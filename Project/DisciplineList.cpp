#include "DisciplineList.hpp"

#include <stdexcept>


DisciplineList::DisciplineList(): m_disciplines() {}

DisciplineList::~DisciplineList() {
	for (Discipline* discipline : m_disciplines) {
		delete discipline;
	}
}

int DisciplineList::GetSize() const {
	return m_disciplines.size();
}

bool DisciplineList::ContainsDiscipline(Discipline* discipline) const {
	for (Discipline* el : m_disciplines) {
		if (el->Equals(*discipline)) {
			return true;
		}
	}
	return false;
}

const std::vector<Discipline*>& DisciplineList::GetDisciplines() const {
	return m_disciplines;
}

DisciplineReferenceList DisciplineList::GetDisciplineReferenceList() const {
	return DisciplineReferenceList(m_disciplines);
}

void DisciplineList::AddDiscipline(Discipline* discipline) {
	if (this->ContainsDiscipline(discipline)) {
		throw std::invalid_argument("Added discipline is already in list");
	}
	m_disciplines.push_back(discipline);
}

void DisciplineList::DeleteDiscipline(Discipline* discipline) {
	for (int i = 0; i < m_disciplines.size(); i++) {
		if (m_disciplines[i]->Equals(*discipline)) {
			delete m_disciplines[i];
			m_disciplines.erase(m_disciplines.begin() + i);
			return;
		}
	}
	throw std::invalid_argument("Deleted discipline is not in list");
}
