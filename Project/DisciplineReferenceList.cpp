#include "DisciplineReferenceList.hpp"


DisciplineReferenceList::DisciplineReferenceList(): m_disciplines() {}

DisciplineReferenceList::DisciplineReferenceList(const std::vector<Discipline*>& disciplines): m_disciplines(disciplines) {}


int DisciplineReferenceList::GetSize() const {
	return m_disciplines.size();
}

Discipline* DisciplineReferenceList::GetDisciplineAt(int index) const {
	return m_disciplines[index];
}

int DisciplineReferenceList::FindDiscipline(Discipline* discipline) const {
	for (int i = 0; i < m_disciplines.size(); i++) {
		if (m_disciplines[i]->Equals(*discipline)) {
			return i;
		}
	}
	return DISCIPLINE_NOT_FOUND;
}

const std::vector<Discipline*>& DisciplineReferenceList::GetDisciplines() const {
	return m_disciplines;
}


void DisciplineReferenceList::AddDiscipline(Discipline* discipline) {
	if (FindDiscipline(discipline) == DISCIPLINE_NOT_FOUND) {
		m_disciplines.push_back(discipline);
	}
}

void DisciplineReferenceList::RemoveDisciplineAt(int index) {
	m_disciplines.erase(m_disciplines.begin() + index);
}

void DisciplineReferenceList::RemoveDiscipline(Discipline* discipline) {
	int index = FindDiscipline(discipline);
	if (index != DISCIPLINE_NOT_FOUND) {
		RemoveDisciplineAt(index);
	}
}
