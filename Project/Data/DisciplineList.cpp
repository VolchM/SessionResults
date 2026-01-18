#include "Data/DisciplineList.hpp"

#include <stdexcept>


DisciplineList::DisciplineList(): m_disciplines() {}

DisciplineList::DisciplineList(const std::vector<std::shared_ptr<Discipline>>& disciplines): m_disciplines(disciplines) {}

DisciplineList::DisciplineList(const DisciplineList& other): m_disciplines(other.m_disciplines) {}

DisciplineList DisciplineList::ShallowClone() const {
	return DisciplineList(m_disciplines);
}

DisciplineList DisciplineList::DeepClone() const {
	DisciplineList disciplineList;
	for (const std::shared_ptr<Discipline>& discipline : m_disciplines) {
		disciplineList.AddDiscipline(std::make_shared<Discipline>(*discipline));
	}
	return disciplineList;
}


int DisciplineList::GetSize() const {
	return m_disciplines.size();
}

std::shared_ptr<Discipline> DisciplineList::GetDisciplineAt(int index) const {
	return m_disciplines[index];
}

int DisciplineList::FindDiscipline(std::shared_ptr<Discipline> discipline) const {
	for (int i = 0; i < m_disciplines.size(); i++) {
		if (*m_disciplines[i] == *discipline) {
			return i;
		}
	}
	return DISCIPLINE_NOT_FOUND;
}

const std::vector<std::shared_ptr<Discipline>>& DisciplineList::GetDisciplines() const {
	return m_disciplines;
}


void DisciplineList::AddDiscipline(std::shared_ptr<Discipline> discipline) {
	if (FindDiscipline(discipline) != DISCIPLINE_NOT_FOUND) {
		throw std::invalid_argument("Added discipline is already in list");
	}
	m_disciplines.push_back(discipline);
}

void DisciplineList::RemoveDisciplineAt(int index) {
	m_disciplines.erase(m_disciplines.begin() + index);
}

void DisciplineList::RemoveDiscipline(std::shared_ptr<Discipline> discipline) {
	int index = FindDiscipline(discipline);
	if (index == DISCIPLINE_NOT_FOUND) {
		throw std::invalid_argument("Deleted discipline is not in list");
	}
	RemoveDisciplineAt(index);
}
