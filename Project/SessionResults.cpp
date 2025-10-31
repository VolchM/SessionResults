#include "SessionResults.hpp"


SessionResults::SessionResults(): m_disciplines(), m_results() {}

SessionResults::~SessionResults() {
	for (AttestationResult* result : m_results) {
		delete result;
	}
}

AttestationResult* SessionResults::GetResult(Discipline* discipline) {
	int index = m_disciplines.FindDiscipline(discipline);
	if (index != -1) {
		return m_results[index];
	} else {
		return nullptr;
	}
}

void SessionResults::SetResult(Discipline* discipline, AttestationResult* result) {
	int index = m_disciplines.FindDiscipline(discipline);
	if (index != -1) {
		delete m_results[index];
		m_results[index] = result;
	} else {
		m_disciplines.AddDiscipline(discipline);
		m_results.push_back(result);
	}
}

void SessionResults::DeleteResult(Discipline* discipline) {
	int index = m_disciplines.FindDiscipline(discipline);
	if (index != -1) {
		m_disciplines.RemoveDisciplineAt(index);
		delete m_results[index];
		m_results.erase(m_results.begin() + index);
	}
}
