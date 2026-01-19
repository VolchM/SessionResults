#pragma once

#include "Data/Group.hpp"
#include "UI/LoopPage.hpp"
#include "UI/StudentPage.hpp"

#include <memory>


class GroupPage : public LoopPage {
private:
	std::shared_ptr<Group> m_group;

public:
	GroupPage(std::shared_ptr<Group> group);

protected:
	void Loop() override;

private:
	void GoToStudent();
	void ChangeGroupName();
	void ChangeGroupCourse();
	void AddStudent();
	void DeleteStudent();
	void PrintStudents();
	int SelectStudent();
};