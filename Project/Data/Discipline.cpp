#include "Data/Discipline.hpp"

#include "StringUtils.hpp"

#include <stdexcept>
#include <format>


Discipline::Discipline(std::string name, AttestationType attestationType) {
	SetName(name);
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

void Discipline::SetName(const std::string& value) {
	std::string newValue = StringUtils::Trim(value);
	if (newValue.size() == 0) {
		throw std::invalid_argument("Discipline name cannot be empty");
	}
	m_name = std::move(newValue);
}

Discipline::AttestationType Discipline::GetAttestationType() const {
	return m_attestationType;
}

void Discipline::SetAttestationType(Discipline::AttestationType value) {
	m_attestationType = value;
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
