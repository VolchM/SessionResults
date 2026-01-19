#include "UI/FacultyPage.hpp"

#include <format>
#include <iostream>


FacultyPage::FacultyPage(std::shared_ptr<Faculty> faculty) {
	m_faculty = faculty;
	SetPicker(std::make_unique<MenuActionPicker>(std::vector<MenuActionPicker::Item>{
		{ "Перейти к специальности", [this]() { GoToSpeciality(); } }, 
		{ "Изменить название факультета", [this]() { ChangeFacultyName(); } },
		{ "Добавить специальность", [this]() { AddSpeciality(); } },
		{ "Удалить специальность", [this]() { DeleteSpeciality(); } },
		{ "Сохранить изменения и вернуться в главное меню", [this]() { StopLoop(); } }
	}));
}

void FacultyPage::Loop() {
	std::cout << std::format("======== {} ========\n", m_faculty->GetName());
	std::cout << "Специальности:\n";
	PrintSpecialities();
}

void FacultyPage::GoToSpeciality() {
	int selectedIndex = SelectSpeciality();
	if (selectedIndex != -1) {
		SpecialityPage(m_faculty->GetSpecialityAt(selectedIndex)).Start();
	}
}

void FacultyPage::ChangeFacultyName() {
	try {
		std::cout << "Введите новое название факультета: ";
		std::string name;
		std::getline(std::cin, name);
		m_faculty->SetName(name);
	} catch (std::invalid_argument) {
		std::cout << "Введено некорректное название\n";
	}
}

void FacultyPage::AddSpeciality() {
	std::cout << "Введите код новой специальности: ";
	std::string code;
	std::getline(std::cin, code);

	std::cout << "Введите название новой специальности: ";
	std::string name;
	std::getline(std::cin, name);

	try {
		m_faculty->AddSpeciality(std::make_shared<Speciality>(code, name));
	} catch (std::invalid_argument) {
		std::cout << "Не удалось добавить специальность\n";
	}
}

void FacultyPage::DeleteSpeciality() {
	int selectedIndex = SelectSpeciality();
	if (selectedIndex != -1) {
		m_faculty->DeleteSpeciality(m_faculty->GetSpecialityAt(selectedIndex));
	}
}

void FacultyPage::PrintSpecialities() {
	for (int i = 0; i < m_faculty->GetSpecialityCount(); i++) {
		std::cout << std::format("{}. {}\n", i + 1, m_faculty->GetSpecialityAt(i)->ToString());
	}
}

int FacultyPage::SelectSpeciality() {
	int value;
	std::cout << "Введите номер специальности: ";
	if ((std::cin >> value) && (value >= 1 && value <= m_faculty->GetSpecialityCount())) {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return value - 1;
	} else {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return -1;
	}
}
