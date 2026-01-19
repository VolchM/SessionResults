#include "UI/ResultsEditingPage.hpp"

#include "Data/AttestationResult.hpp"
#include "Data/ExamResult.hpp"
#include "Data/PassFailExamResult.hpp"
#include "UI/QuickItemPicker.hpp"

#include <format>
#include <iostream>


ResultsEditingPage::ResultsEditingPage(std::shared_ptr<Group> group, std::shared_ptr<Discipline> discipline) {
	m_group = group;
	m_discipline = discipline;
	SetPicker(std::make_unique<MenuActionPicker>(std::vector<MenuActionPicker::Item>{
		{ "Изменить результат", [this]() { ChangeResult(); } },
		{ "Удалить результат", [this]() { DeleteResult(); } },
		{ "Сохранить изменения и вернуться в главное меню", [this]() { StopLoop(); } }
	}));
}

void ResultsEditingPage::Loop() {
	std::cout << std::format("======== {}, {} ========\n", m_group->ToString(), m_discipline->ToString());
	PrintResults();
}

void ResultsEditingPage::ChangeResult() {
	int selectedIndex = SelectStudent();
	if (selectedIndex != -1) {
		std::shared_ptr<AttestationResult> newResult = ReadResult();
		m_group->GetStudentAt(selectedIndex)->GetSessionResults().SetResult(m_discipline, newResult);
	}
}

void ResultsEditingPage::DeleteResult() {
	int selectedIndex = SelectStudent();
	if (selectedIndex != -1) {
		m_group->GetStudentAt(selectedIndex)->GetSessionResults().DeleteResult(m_discipline);
	}
}

void ResultsEditingPage::PrintResults() {
	for (int i = 0; i < m_group->GetStudentCount(); i++) {
		std::shared_ptr<Student> student = m_group->GetStudentAt(i);
		std::shared_ptr<AttestationResult> result = student->GetSessionResults().GetResult(m_discipline);
		std::cout << std::format("{}. {}  -  {}\n", i + 1, student->ToString(), result ? result->ToString() : "Нет результата");
	}
}

int ResultsEditingPage::SelectStudent() {
	int value;
	std::cout << "Введите порядковый номер студента: ";
	if ((std::cin >> value) && (value >= 1 && value <= m_group->GetStudentCount())) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return value - 1;
	} else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Введён неверный номер\n";
		return -1;
	}
}

std::shared_ptr<AttestationResult> ResultsEditingPage::ReadResult() {
	switch (m_discipline->GetAttestationType()) {
	case Discipline::AttestationType::ePassFailExam:
		return ReadPassFailExamResult();
	case Discipline::AttestationType::eExam:
		return ReadExamResult();
	}
}

std::shared_ptr<PassFailExamResult> ResultsEditingPage::ReadPassFailExamResult() {
	QuickItemPicker resultPicker({"Незачёт", "Зачёт"});
	std::cout << "Выберите результат:\n";
	int choice = resultPicker.Pick();
	return std::make_shared<PassFailExamResult>(choice == 1);
}

std::shared_ptr<ExamResult> ResultsEditingPage::ReadExamResult() {
	while (true) {
		try {
			std::cout << std::format("Введите новый результат (от {} до {}): ",
				ExamResult::MIN_SCORE, ExamResult::MAX_SCORE);
			std::string input;
			std::getline(std::cin, input);
			int score = std::stoi(input);
			return std::make_shared<ExamResult>(score);
		} catch (std::invalid_argument) {
			std::cout << "Введён некорректный результат\n";
		} catch (std::out_of_range) {
			std::cout << "Введён некорректный результат\n";
		}
	}
}
