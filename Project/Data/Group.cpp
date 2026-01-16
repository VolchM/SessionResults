#include "Data/Group.hpp"

#include "StringUtils.hpp"
#include "Data/Speciality.hpp"

#include <stdexcept>
#include <format>


Group::Group(const std::string& name, int course) {
    SetName(name);
    SetCourse(course);
}


std::string Group::ToString() const {
    return std::format("{} - {} курс", m_name, m_course);
}

const std::string& Group::GetName() const {
    return m_name;
}

void Group::SetName(const std::string& value) {
    std::string newValue = StringUtils::Trim(value);
    if (newValue.size() == 0) {
        throw std::invalid_argument("Group name cannot be empty");
    }
    m_name = std::move(newValue);
}

int Group::GetCourse() const {
    return m_course;
}

void Group::SetCourse(int value) {
    if (!(value >= Speciality::MIN_COURSE && value <= Speciality::MAX_COURSE)) {
        throw std::invalid_argument("Invalid course value");
    }
    m_course = value;
}

std::weak_ptr<Speciality> Group::GetSpeciality() const {
    return m_speciality;
}

const DisciplineList& Group::GetDisciplineList() const {
    std::shared_ptr<Speciality> speciality = m_speciality.lock();
    if (!speciality) {
        throw std::runtime_error("Group's speciality is not set or no longer exist");
    }
    return speciality->GetDisciplineList(m_course);
}


int Group::GetStudentCount() const {
    return m_students.size();
}

std::shared_ptr<Student> Group::GetStudentAt(int index) const {
    return m_students[index];
}

const std::vector<std::shared_ptr<Student>>& Group::GetStudents() const {
    return m_students;
}

int Group::FindStudentByID(unsigned int studentID) const {
    for (int i = 0; i < m_students.size(); i++) {
        if (m_students[i]->GetStudentID() == studentID) {
            return i;
        }
    }
    return STUDENT_NOT_FOUND;
}

void Group::AddStudent(std::shared_ptr<Student> student) {
    if (FindStudentByID(student->GetStudentID()) != STUDENT_NOT_FOUND) {
        throw std::invalid_argument("Added student is already in group");
    }
    if (!student->m_group.expired()) {
        throw std::runtime_error("Student is already in another group");
    }
    m_students.push_back(student);
    student->m_group = weak_from_this();
}

void Group::DeleteStudentByID(unsigned int studentID) {
    int index = FindStudentByID(studentID);
    if (index == STUDENT_NOT_FOUND) {
        throw std::invalid_argument("Deleted student is not in group");
    }
    m_students[index]->m_group.reset();
    m_students.erase(m_students.begin() + index);
}

void Group::DeleteStudent(std::shared_ptr<Student> student) {
    DeleteStudentByID(student->GetStudentID());
}
