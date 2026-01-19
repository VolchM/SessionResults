#include "UI/DisciplineListPage.hpp"

#include <format>
#include <ranges>
#include <algorithm>


DisciplineListPage::DisciplineListPage(std::shared_ptr<Speciality> speciality, int course) :
	m_speciality(speciality),
	m_disciplineList(speciality->GetDisciplineList(course)),
	m_course(course) 
{
	m_picker = std::make_unique<MenuActionPicker>(std::vector<MenuActionPicker::Item>{
		{ "Изменить название дисциплины", [this]() { ChangeDisciplineName(); } },
		{ "Добавить дисциплину", [this]() { AddDiscipline(); } },
		{ "Удалить дисциплину", [this]() { DeleteDiscipline(); } },
		{ "Назад", [this]() { StopLoop(); } }
	});
}

void DisciplineListPage::Loop() {
	std::cout << std::format("==== Дисциплины - {} курс ====\n", m_course);
	PrintDisciplines();
	std::cout << "Действия:\n";
	m_picker->PickAndRun();
}

void DisciplineListPage::ChangeDisciplineName() {
	int selectedIndex = SelectDiscipline();
	if (selectedIndex != -1) {
		std::shared_ptr<Discipline> oldDiscipline = m_disciplineList.GetDisciplineAt(selectedIndex);

		try {
			std::cout << "Введите новое название дисциплины: ";
			std::string name;
			std::getline(std::cin, name);

			std::shared_ptr<Discipline> newDiscipline = std::make_shared<Discipline>(name, oldDiscipline->GetAttestationType());

			m_disciplineList.RemoveDiscipline(oldDiscipline);
			m_disciplineList.AddDiscipline(newDiscipline);

			for (auto& group : m_speciality->GetGroups() | std::views::filter([&](auto& group) { return group->GetCourse() == m_course; })) {
				for (auto& student : group->GetStudents()) {
					std::shared_ptr<AttestationResult> result = student->GetSessionResults().GetResult(oldDiscipline);
					if (result != nullptr) {
						student->GetSessionResults().DeleteResult(oldDiscipline);
						student->GetSessionResults().SetResult(newDiscipline, result);
					}
				}
			}
		} catch (std::invalid_argument) {
			std::cout << "Не удалось изменить дисциплину\n";
		}
	}
}

void DisciplineListPage::AddDiscipline() {
	std::cout << "Введите название новой дисциплины: ";
	std::string name;
	std::getline(std::cin, name);

	std::cout << "Выберите тип аттестации новой дисциплины:\n";
	Discipline::AttestationType attestationType = PickAttestationType();

	try {
		m_disciplineList.AddDiscipline(std::make_shared<Discipline>(name, attestationType));
	} catch (std::invalid_argument) {
		std::cout << "Не удалось добавить дисциплину\n";
	}
}

void DisciplineListPage::DeleteDiscipline() {
	int selectedIndex = SelectDiscipline();
	if (selectedIndex != -1) {
		std::shared_ptr<Discipline> deletedDiscipline = m_disciplineList.GetDisciplineAt(selectedIndex);

		for (auto& group : m_speciality->GetGroups() | std::views::filter([&](auto& group) { return group->GetCourse() == m_course; })) {
			for (auto& student : group->GetStudents()) {
				student->GetSessionResults().DeleteResult(deletedDiscipline);
			}
		}

		m_disciplineList.RemoveDisciplineAt(selectedIndex);
	}
}

void DisciplineListPage::PrintDisciplines() {
	for (int i = 0; i < m_disciplineList.GetSize(); i++) {
		std::cout << std::format("{}. {}\n", i + 1, m_disciplineList.GetDisciplineAt(i)->ToString());
	}
}

Discipline::AttestationType DisciplineListPage::PickAttestationType() {
	QuickItemPicker attestationTypePicker({"Экзамен", "Зачёт"});
	int selected = attestationTypePicker.Pick();
	switch (selected) {
		case 0: return Discipline::AttestationType::eExam;
		case 1: return Discipline::AttestationType::ePassFailExam;
	}
}

int DisciplineListPage::SelectDiscipline() {
	int value;
	std::cout << "Введите номер дисциплины: ";
	if ((std::cin >> value) && (value >= 1 && value <= m_disciplineList.GetSize())) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return value - 1;
	} else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Введён неверный номер\n";
		return -1;
	}
}