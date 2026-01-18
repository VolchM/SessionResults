#pragma once

#include "Data/Faculty.hpp"
#include "UI/LoopPage.hpp"
#include "UI/MenuActionPicker.hpp"
#include "UI/SpecialityPage.hpp"

#include <memory>


class FacultyPage : public LoopPage {
private:
	std::shared_ptr<Faculty> m_faculty;
	std::unique_ptr<MenuActionPicker> m_picker;

public:
	FacultyPage(std::shared_ptr<Faculty> faculty);

protected:
	void Loop() override;

private:
	void GoToSpeciality();
	void ChangeFacultyName();
	void AddSpeciality();
	void DeleteSpeciality();
	void PrintSpecialities();
	int SelectSpeciality();
};