#include "Discipline.hpp"

#include "StringUtils.hpp"

#include <stdexcept>


Discipline::Discipline(std::string name, AttestationType attestationType) {
	this->SetName(name);
	m_attestationType = attestationType;
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
