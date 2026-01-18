#pragma once

#include "Data/Faculty.hpp"
#include "Data/FacultyJsonStorage.hpp"
#include "UI/LoopPage.hpp"
#include "UI/MenuActionPicker.hpp"
#include "UI/FacultyPage.hpp"
#include "UI/ResultsSelectPage.hpp"
#include "UI/GroupTablePage.hpp"

#include <memory>


class MainMenuPage : public LoopPage {
private:
	std::string m_fileName;
	std::unique_ptr<IFacultyStorage> m_storage;
	std::unique_ptr<MenuActionPicker> m_picker;

public:
	MainMenuPage(const std::string& fileName);

protected:
	void Loop() override;

private:
	void GoToGroupTablePage();
	void GoToFacultyPage();
	void GoToResultsEditingPage();
	void SelectFile();
	void CreateNewFile();
	std::shared_ptr<Faculty> TryLoadFaculty();
	void TrySaveFaculty(std::shared_ptr<Faculty> faculty);
};

