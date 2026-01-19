#include "UI/MainMenuPage.hpp"


MainMenuPage::MainMenuPage(const std::string& fileName) {
	m_fileName = fileName;
	m_storage = std::make_unique<FacultyJsonStorage>(m_fileName);
	SetPicker(std::make_unique<MenuActionPicker>(std::vector<MenuActionPicker::Item>{
		{ "Создание таблицы успеваемости группы и экспорт", [this]() { GoToGroupTablePage(); } },
		{ "Изменение информации факультета", [this]() { GoToFacultyPage(); } },
		{ "Изменение результатов аттестации", [this]() { GoToResultsEditingPage(); } },
		{ "Выбрать файл", [this]() { SelectFile(); } },
		{ "Создать новый файл", [this]() { CreateNewFile(); } },
		{ "Выход из программы", [this]() { StopLoop(); } },
	}));
}


void MainMenuPage::Loop() {
	std::cout << "========== Главное меню ==========\n";
	std::cout << "Выбранный файл: " << m_fileName << "\n";
}

void MainMenuPage::GoToGroupTablePage() {
	std::shared_ptr<Faculty> faculty = TryLoadFaculty();
	if (faculty != nullptr) {
		GroupTablePage(faculty).Start();
	}
}

void MainMenuPage::GoToFacultyPage() {
	std::shared_ptr<Faculty> faculty = TryLoadFaculty();
	if (faculty != nullptr) {
		FacultyPage(faculty).Start();
		TrySaveFaculty(faculty);
	}
}

void MainMenuPage::GoToResultsEditingPage() {
	std::shared_ptr<Faculty> faculty = TryLoadFaculty();
	if (faculty != nullptr) {
		ResultsSelectPage(faculty).Start();
		TrySaveFaculty(faculty);
	}
}

void MainMenuPage::SelectFile() {
	std::cout << "Введите имя файла: ";
	std::getline(std::cin, m_fileName);

	m_storage = std::make_unique<FacultyJsonStorage>(m_fileName);
}

void MainMenuPage::CreateNewFile() {
	std::cout << "Введите имя файла: ";
	std::getline(std::cin, m_fileName);
	m_storage = std::make_unique<FacultyJsonStorage>(m_fileName);

	std::cout << "Введите имя факультета: ";
	std::string facultyName;
	std::getline(std::cin, facultyName);

	try {
		TrySaveFaculty(std::make_shared<Faculty>(facultyName));
	} catch (std::invalid_argument) {
		std::cout << "Введено некорректное название факультета\n";
	}
}

std::shared_ptr<Faculty> MainMenuPage::TryLoadFaculty() {
	try {
		return m_storage->Load();
	} catch (std::exception) {
		std::cout << "Не удалось загрузить данные факультета из файла\n";
		return nullptr;
	}
}

void MainMenuPage::TrySaveFaculty(std::shared_ptr<Faculty> faculty) {
	try {
		m_storage->Save(faculty);
	} catch (std::exception) {
		std::cout << "Не удалось сохранить изменения факультета в файл\n";
	}
}
