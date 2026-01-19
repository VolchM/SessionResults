#include "UI/GroupPage.hpp"

#include "Data/Speciality.hpp"

#include <format>
#include <iostream>


GroupPage::GroupPage(std::shared_ptr<Group> group) {
	m_group = group;
	SetPicker(std::make_unique<MenuActionPicker>(std::vector<MenuActionPicker::Item>{
		{ "Перейти к студенту", [this]() { GoToStudent(); } },
		{ "Изменить название группы", [this]() { ChangeGroupName(); } },
		{ "Изменить курс группы", [this]() { ChangeGroupCourse(); } },
		{ "Добавить студента", [this]() { AddStudent(); } },
		{ "Удалить студента", [this]() { DeleteStudent(); } },
		{ "Назад", [this]() { StopLoop(); } }
	}));
}

void GroupPage::Loop() {
	std::cout << std::format("==== {} ====\n", m_group->ToString());
	std::cout << "Студенты:\n";
	PrintStudents();
}

void GroupPage::GoToStudent() {
	int selectedIndex = SelectStudent();
	if (selectedIndex != -1) {
		StudentPage(m_group->GetStudentAt(selectedIndex)).Start();
	}
}

void GroupPage::ChangeGroupName() {
	try {
		std::cout << "Введите новое название группы: ";
		std::string name;
		std::getline(std::cin, name);
		m_group->SetName(name);
	} catch (std::invalid_argument) {
		std::cout << "Введено некорректное название\n";
	}
}

void GroupPage::ChangeGroupCourse() {
	try {
		std::cout << "Введите новый курс группы: ";
		std::string input;
		std::getline(std::cin, input);
		int course = std::stoi(input);
		m_group->SetCourse(course);
	} catch (std::invalid_argument) {
		std::cout << "Введен некорректный курс\n";
	} catch (std::out_of_range) {
		std::cout << "Введен некорректный курс\n";
	}
}

void GroupPage::AddStudent() {
	std::cout << "Введите номер студенческого билета нового студента: ";
	std::string studentIDInput;
	std::getline(std::cin, studentIDInput);

	std::cout << "Введите имя нового студента: ";
	std::string firstName;
	std::getline(std::cin, firstName);

	std::cout << "Введите фамилию нового студента: ";
	std::string lastName;
	std::getline(std::cin, lastName);

	std::cout << "Введите отчество нового студента: ";
	std::string middleName;
	std::getline(std::cin, middleName);

	try {
		unsigned int studentID = std::stoul(studentIDInput);
		m_group->AddStudent(std::make_shared<Student>(studentID, firstName, lastName, middleName));
	} catch (std::invalid_argument) {
		std::cout << "Не удалось добавить студента\n";
	} catch (std::out_of_range) {
		std::cout << "Не удалось добавить студента\n";
	}
}

void GroupPage::DeleteStudent() {
	int selectedIndex = SelectStudent();
	if (selectedIndex != -1) {
		m_group->DeleteStudent(m_group->GetStudentAt(selectedIndex));
	}
}

void GroupPage::PrintStudents() {
	for (int i = 0; i < m_group->GetStudentCount(); i++) {
		std::cout << std::format("{}. {}\n", i + 1, m_group->GetStudentAt(i)->ToString());
	}
}

int GroupPage::SelectStudent() {
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