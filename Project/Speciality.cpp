#include "Speciality.hpp"

#include "StringUtils.hpp"

#include <stdexcept>


Speciality::Speciality(const std::string& code, const std::string& name) {
    SetCode(code);
    SetName(name);
}


const std::string& Speciality::GetCode() const {
    return m_code;
}

void Speciality::SetCode(const std::string& value) {
    if (StringUtils::ConstainsSpacesOrEmpty(value)) {
        throw std::invalid_argument("Speciality code cannot contain spaces or be empty");
    }
    m_code = value;
}

const std::string& Speciality::GetName() const {
    return m_name;
}

void Speciality::SetName(const std::string& value) {
    std::string newValue = StringUtils::Trim(value);
    if (newValue.size() == 0) {
        throw std::invalid_argument("Speciality name cannot be empty");
    }
    m_name = std::move(newValue);
}

DisciplineList& Speciality::GetDisciplineList(int course) {
    if (!(course >= MIN_COURSE && course <= MAX_COURSE)) {
        throw std::invalid_argument("Invalid course value");
    }
    return m_disciplines[course-1];
}

int Speciality::GetGroupCount() const {
    return m_groups.size();
}

std::shared_ptr<Group> Speciality::GetGroupAt(int index) const {
    return m_groups[index];
}

const std::vector<std::shared_ptr<Group>>& Speciality::GetGroups() const {
    return m_groups;
}

int Speciality::FindGroupByName(const std::string& name) const {
    for (int i = 0; i < m_groups.size(); i++) {
        if (m_groups[i]->GetName() == name) {
            return i;
        }
    }
    return GROUP_NOT_FOUND;
}

void Speciality::AddGroup(std::shared_ptr<Group> group) {
    if (FindGroupByName(group->GetName()) != GROUP_NOT_FOUND) {
        throw std::invalid_argument("Speciality already contains added group");
    }
    m_groups.push_back(group);
}

void Speciality::DeleteGroupByName(const std::string& name) {
    int index = FindGroupByName(name);
    if (index == GROUP_NOT_FOUND) {
        throw std::invalid_argument("Speciality doesn't contain deleted group");
    }
    m_groups.erase(m_groups.begin() + index);
}

void Speciality::DeleteGroup(std::shared_ptr<Group> group) {
    DeleteGroupByName(group->GetName());
}
