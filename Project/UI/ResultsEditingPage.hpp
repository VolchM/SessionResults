#pragma once

#include "Data/Group.hpp"
#include "Data/Discipline.hpp"
#include "UI/LoopPage.hpp"
#include "UI/MenuActionPicker.hpp"


#include <memory>


class ResultsEditingPage : public LoopPage {
private:
	std::shared_ptr<Group> m_group;
	std::shared_ptr<Discipline> m_discipline;
	std::unique_ptr<MenuActionPicker> m_picker;

public:
	ResultsEditingPage(std::shared_ptr<Group> group, std::shared_ptr<Discipline> discipline);

protected:
	void Loop() override;

private:
	void ChangeResult();
	void DeleteResult();
	void PrintResults();
	int SelectStudent();
	std::shared_ptr<AttestationResult> ReadResult();
	std::shared_ptr<PassFailExamResult> ReadPassFailExamResult();
	std::shared_ptr<ExamResult> ReadExamResult();
};