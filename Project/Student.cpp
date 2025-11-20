#include "Student.hpp"

#include "StringUtils.hpp"

#include <stdexcept>


Student::Student(std::shared_ptr<Group> group, unsigned int studentID, const std::string& firstName, const std::string& lastName, const std::string& middleName) {
    if (group == nullptr) {
        throw std::invalid_argument("Group cannot be nullptr");
    }
    m_group = group;
    m_studentID = studentID;
    SetFirstName(firstName);
    SetLastName(lastName);
    SetMiddleName(middleName);
}

unsigned int Student::GetStudentID() const {
    return m_studentID;
}

void Student::SetStudentID(unsigned int value) {
    m_studentID = value;
}

const std::string& Student::GetFirstName() const {
    return m_firstName;
}

void Student::SetFirstName(const std::string& value) {
    if (StringUtils::ConstainsSpacesOrEmpty(value)) {
        throw std::invalid_argument("First name cannot contain spaces or be empty");
    }
    m_firstName = value;
}

const std::string& Student::GetLastName() const {
    return m_lastName;
}

void Student::SetLastName(const std::string& value) {
    if (StringUtils::ConstainsSpacesOrEmpty(value)) {
        throw std::invalid_argument("Last name cannot contain spaces or be empty");
    }
    m_lastName = value;
}

const std::string& Student::GetMiddleName() const {
    return m_middleName;
}

void Student::SetMiddleName(const std::string& value) {
    if (StringUtils::ConstainsSpacesOrEmpty(value)) {
        throw std::invalid_argument("Middle name cannot contain spaces or be empty");
    }
    m_middleName = value;
}

std::string Student::GetFullName() const {
    return m_firstName + " " + m_lastName + " " + m_middleName;
}

std::string Student::GetLastNameWithInitials() const {
    return m_lastName + " " + m_firstName[0] + ". " + m_middleName[0] + ".";
}

std::weak_ptr<Group> Student::GetGroup() const {
    return m_group;
}

SessionResults& Student::GetSessionResults() {
    return m_sessionResults;
}
