#include "Group.hpp"

#include "StringUtils.hpp"

#include <stdexcept>


Group::Group(Speciality* speciality, const std::string& name, int course) {
    if (speciality == nullptr) {
        throw std::invalid_argument("Speciality cannot be nullptr");
    }
    m_speciality = speciality;
    SetName(name);
    SetCourse(course);
}

Group::~Group() {
    for (Student* student : m_students) {
        delete student;
    }
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
    if (!(value >= 1 && value <= 4)) {
        throw std::invalid_argument("Course must be a number between 1 and 4");
    }
    m_course = value;
}

Speciality* Group::GetSpeciality() const {
    return m_speciality;
}

int Group::GetStudentCount() const {
    return m_students.size();
}

Student* Group::GetStudentAt(int index) const {
    return m_students[index];
}

const std::vector<Student*>& Group::GetStudents() const {
    return m_students;
}

int Group::FindStudentByID(unsigned int studentID) const {
    for (int i = 0; i < m_students.size(); i++) {
        if (m_students[i]->GetStudentID() == studentID) {
            return i;
        }
    }
    return -1;
}

void Group::AddStudent(Student* student) {
    if (FindStudentByID(student->GetStudentID()) != -1) {
        throw std::invalid_argument("Added student is already in group");
    }
    m_students.push_back(student);
}

void Group::DeleteStudentByID(unsigned int studentID) {
    int index = FindStudentByID(studentID);
    if (index == -1) {
        throw std::invalid_argument("Deleted student is not in group");
    }
    delete m_students[index];
    m_students.erase(m_students.begin() + index);
}

void Group::DeleteStudent(Student* student) {
    DeleteStudentByID(student->GetStudentID());
}
