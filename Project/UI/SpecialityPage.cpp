#include "UI/SpecialityPage.hpp"

#include <format>
#include <iostream>


SpecialityPage::SpecialityPage(std::shared_ptr<Speciality> speciality) {
	m_speciality = speciality;
	m_picker = std::make_unique<MenuActionPicker>(std::vector<MenuActionPicker::Item>{
		{ "Перейти к группе", [this]() { GoToGroup(); } },
		{ "Перейти к списку дисциплин", [this]() { GoToDisciplineList(); } },
		{ "Изменить код специальности", [this]() { ChangeSpecialityCode(); } },
		{ "Изменить название специальности", [this]() { ChangeSpecialityName(); } },
		{ "Добавить группу", [this]() { AddGroup(); } },
		{ "Удалить группу", [this]() { DeleteGroup(); } },
		{ "Назад", [this]() { StopLoop(); } }
	});
}

void SpecialityPage::Loop() {
	std::cout << std::format("====== {} ======\n", m_speciality->ToString());
	std::cout << "Группы:\n";
	PrintGroups();
	std::cout << "Действия:\n";
	m_picker->PickAndRun();
}

void SpecialityPage::GoToGroup() {
	int selectedIndex = SelectGroup();
	if (selectedIndex != -1) {
		GroupPage(m_speciality->GetGroupAt(selectedIndex)).Start();
	}
}

void SpecialityPage::GoToDisciplineList() {
	std::cout << std::format("Введите курс ({}-{}): ", Speciality::MIN_COURSE, Speciality::MAX_COURSE);

	int course;
	if ((std::cin >> course) && (course >= Speciality::MIN_COURSE && course <= Speciality::MAX_COURSE)) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		DisciplineListPage(m_speciality, course).Start();
	} else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Введен некорректный курс\n";
	}
}

void SpecialityPage::ChangeSpecialityCode() {
	try {
		std::cout << "Введите новый код специальности: ";
		std::string code;
		std::getline(std::cin, code);
		m_speciality->SetCode(code);
	} catch (std::invalid_argument) {
		std::cout << "Введен некорректный код\n";
	}
}

void SpecialityPage::ChangeSpecialityName() {
	try {
		std::cout << "Введите новое название специальности: ";
		std::string name;
		std::getline(std::cin, name);
		m_speciality->SetName(name);
	} catch (std::invalid_argument) {
		std::cout << "Введено некорректное название\n";
	}
}

void SpecialityPage::AddGroup() {
	std::cout << "Введите название новой группы: ";
	std::string name;
	std::getline(std::cin, name);

	std::cout << "Введите курс новой группы: ";
	std::string courseInput;
	std::getline(std::cin, courseInput);

	try {
		int course = std::stoi(courseInput);
		m_speciality->AddGroup(std::make_shared<Group>(name, course));
	} catch (std::invalid_argument) {
		std::cout << "Не удалось добавить группу\n";
	} catch (std::out_of_range) {
		std::cout << "Не удалось добавить группу\n";
	}
}

void SpecialityPage::DeleteGroup() {
	int selectedIndex = SelectGroup();
	if (selectedIndex != -1) {
		m_speciality->DeleteGroup(m_speciality->GetGroupAt(selectedIndex));
	}
}

void SpecialityPage::PrintGroups() {
	for (int i = 0; i < m_speciality->GetGroupCount(); i++) {
		std::cout << std::format("{}. {}\n", i + 1, m_speciality->GetGroupAt(i)->ToString());
	}
}

int SpecialityPage::SelectGroup() {
	int value;
	std::cout << "Введите номер группы: ";
	if ((std::cin >> value) && (value >= 1 && value <= m_speciality->GetGroupCount())) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return value - 1;
	} else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Введён неверный номер\n";
		return -1;
	}
}