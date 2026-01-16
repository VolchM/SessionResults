#include "Data/Faculty.hpp"

#include "StringUtils.hpp"

#include <stdexcept>


Faculty::Faculty(const std::string& name) {
    SetName(name);
}


std::string Faculty::ToString() const {
    return m_name;
}

const std::string& Faculty::GetName() const {
    return m_name;
}

void Faculty::SetName(const std::string& value) {
    std::string newValue = StringUtils::Trim(value);
    if (newValue.size() == 0) {
        throw std::invalid_argument("Faculty name cannot be empty");
    }
    m_name = std::move(newValue);
}

int Faculty::GetSpecialityCount() const {
    return m_specialities.size();
}

std::shared_ptr<Speciality> Faculty::GetSpecialityAt(int index) const {
    return m_specialities[index];
}

const std::vector<std::shared_ptr<Speciality>>& Faculty::GetSpecialities() const {
    return m_specialities;
}

int Faculty::FindSpecialityByCode(const std::string& code) const {
    for (int i = 0; i < m_specialities.size(); i++) {
        if (m_specialities[i]->GetCode() == code) {
            return i;
        }
    }
    return SPECIALITY_NOT_FOUND;
}


void Faculty::AddSpeciality(std::shared_ptr<Speciality> speciality) {
    if (FindSpecialityByCode(speciality->GetCode()) != SPECIALITY_NOT_FOUND) {
        throw std::invalid_argument("Faculty already contains added speciality");
    }
    if (!speciality->m_faculty.expired()) {
        throw std::runtime_error("Speciality is already added to another faculty");
    }
    m_specialities.push_back(speciality);
    speciality->m_faculty = weak_from_this();
}

void Faculty::DeleteSpecialityByCode(const std::string& code) {
    int index = FindSpecialityByCode(code);
    if (index == SPECIALITY_NOT_FOUND) {
        throw std::invalid_argument("Faculty doesn't contain deleted speciality");
    }
    m_specialities[index]->m_faculty.reset();
    m_specialities.erase(m_specialities.begin() + index);
}

void Faculty::DeleteSpeciality(std::shared_ptr<Speciality> Speciality) {
    DeleteSpecialityByCode(Speciality->GetCode());
}
