#pragma once

#include "Data/Student.hpp"
#include "UI/LoopPage.hpp"

#include <memory>


class StudentPage : public LoopPage {
private:
	std::shared_ptr<Student> m_student;

public:
	StudentPage(std::shared_ptr<Student> student);

protected:
	void Loop() override;

private:
	void ChangeStudentID();
	void ChangeStudentFirstName();
	void ChangeStudentLastName();
	void ChangeStudentMiddleName();
};