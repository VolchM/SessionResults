#include "Data/SessionResults.hpp"


SessionResults::SessionResults(): m_disciplines(), m_results() {}

SessionResults::SessionResults(const SessionResults& other): m_disciplines(other.m_disciplines), m_results(other.m_results) {}


const DisciplineList& SessionResults::GetDisciplineList() const {
	return m_disciplines;
}

std::shared_ptr<AttestationResult> SessionResults::GetResult(std::shared_ptr<Discipline> discipline) const {
	int index = m_disciplines.FindDiscipline(discipline);
	if (index != -1) {
		return m_results[index];
	} else {
		return nullptr;
	}
}

void SessionResults::SetResult(std::shared_ptr<Discipline> discipline, std::shared_ptr<AttestationResult> result) {
	int index = m_disciplines.FindDiscipline(discipline);
	if (index != -1) {
		m_results[index] = result;
	} else {
		m_disciplines.AddDiscipline(discipline);
		m_results.push_back(result);
	}
}

void SessionResults::DeleteResult(std::shared_ptr<Discipline> discipline) {
	int index = m_disciplines.FindDiscipline(discipline);
	if (index != -1) {
		m_disciplines.RemoveDisciplineAt(index);
		m_results.erase(m_results.begin() + index);
	}
}
