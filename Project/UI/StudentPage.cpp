#include "UI/StudentPage.hpp"

#include <format>
#include <iostream>


StudentPage::StudentPage(std::shared_ptr<Student> student) {
	m_student = student;
	SetPicker(std::make_unique<MenuActionPicker>(std::vector<MenuActionPicker::Item>{
		{ "Изменить номер студенческого билета", [this]() { ChangeStudentID(); } },
		{ "Изменить имя студента", [this]() { ChangeStudentFirstName(); } },
		{ "Изменить фамилию студента", [this]() { ChangeStudentLastName(); } },
		{ "Изменить отчество студента", [this]() { ChangeStudentMiddleName(); } },
		{ "Назад", [this]() { StopLoop(); } }
	}));
}

void StudentPage::Loop() {
	std::cout << std::format("== {} ==\n", m_student->ToString());
}

void StudentPage::ChangeStudentID() {
	try {
		std::cout << "Введите новый номер студенческого билета: ";
		std::string studentIDInput;
		std::getline(std::cin, studentIDInput);
		unsigned int studentID = std::stoul(studentIDInput);
		m_student->SetStudentID(studentID);
	} catch (std::invalid_argument) {
		std::cout << "Введен некорректный номер\n";
	} catch (std::out_of_range) {
		std::cout << "Введен некорректный номер\n";
	}
}

void StudentPage::ChangeStudentFirstName() {
	try {
		std::cout << "Введите новое имя студента: ";
		std::string firstName;
		std::getline(std::cin, firstName);
		m_student->SetFirstName(firstName);
	} catch (std::invalid_argument) {
		std::cout << "Введено некорректное имя\n";
	}
}

void StudentPage::ChangeStudentLastName() {
	try {
		std::cout << "Введите новую фамилию студента: ";
		std::string lastName;
		std::getline(std::cin, lastName);
		m_student->SetLastName(lastName);
	} catch (std::invalid_argument) {
		std::cout << "Введена некорректная фамилия\n";
	}
}

void StudentPage::ChangeStudentMiddleName() {
	try {
		std::cout << "Введите новое отчество студента: ";
		std::string middleName;
		std::getline(std::cin, middleName);
		m_student->SetMiddleName(middleName);
	} catch (std::invalid_argument) {
		std::cout << "Введено некорректное отчество\n";
	}
}