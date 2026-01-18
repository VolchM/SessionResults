#pragma once

#include "Data/Speciality.hpp"
#include "UI/LoopPage.hpp"
#include "UI/MenuActionPicker.hpp"
#include "UI/GroupPage.hpp"
#include "UI/DisciplineListPage.hpp"

#include <memory>


class SpecialityPage : public LoopPage {
private:
	std::shared_ptr<Speciality> m_speciality;
	std::unique_ptr<MenuActionPicker> m_picker;

public:
	SpecialityPage(std::shared_ptr<Speciality> speciality);

protected:
	void Loop() override;

private:
	void GoToGroup();
	void GoToDisciplineList();
	void ChangeSpecialityCode();
	void ChangeSpecialityName();
	void AddGroup();
	void DeleteGroup();
	void PrintGroups();
	int SelectGroup();
};