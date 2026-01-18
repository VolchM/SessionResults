#pragma once

#include "Data/Speciality.hpp"
#include "UI/LoopPage.hpp"
#include "UI/MenuActionPicker.hpp"
#include "UI/QuickItemPicker.hpp"

#include <memory>


class DisciplineListPage : public LoopPage {
private:
	std::shared_ptr<Speciality> m_speciality;
	int m_course;
	DisciplineList& m_disciplineList;
	std::unique_ptr<MenuActionPicker> m_picker;

public:
	DisciplineListPage(std::shared_ptr<Speciality> speciality, int course);

protected:
	void Loop() override;

private:
	void ChangeDisciplineName();
	void AddDiscipline();
	void DeleteDiscipline();
	void PrintDisciplines();
	Discipline::AttestationType PickAttestationType();
	int SelectDiscipline();
};