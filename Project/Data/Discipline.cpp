#include "Data/Discipline.hpp"

#include "StringUtils.hpp"

#include <stdexcept>
#include <format>


Discipline::Discipline(std::string name, AttestationType attestationType) {
	std::string trimmedName = StringUtils::Trim(name);
	if (trimmedName.size() == 0) {
		throw std::invalid_argument("Discipline name cannot be empty");
	}
	m_name = std::move(trimmedName);
	m_attestationType = attestationType;
}

Discipline::Discipline(const Discipline& other): m_name(other.m_name), m_attestationType(other.m_attestationType) {}


std::string Discipline::ToString() const {
	switch (m_attestationType) {
	case AttestationType::eExam:
		return std::format("{} - Экзамен", m_name);
	case AttestationType::ePassFailExam:
		return std::format("{} - Зачёт", m_name);
	}
}

const std::string& Discipline::GetName() const {
	return m_name;
}

Discipline::AttestationType Discipline::GetAttestationType() const {
	return m_attestationType;
}

bool Discipline::Equals(const Discipline& other) const {
	return m_name == other.GetName() && m_attestationType == other.GetAttestationType();
}

bool Discipline::operator==(const Discipline& other) {
	return this->Equals(other);
}

bool Discipline::operator!=(const Discipline& other) {
	return !(*this == other);
}
