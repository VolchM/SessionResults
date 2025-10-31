#include "GroupTableData.hpp"


GroupTableData::GroupTableData(const std::vector<Student*>& students, const std::vector<Discipline*>& disciplines,
	const std::vector<std::vector<AttestationResult*>>& tableBody) :
	m_students(students), m_disciplines(disciplines), m_tableBody(tableBody) { }

GroupTableData::GroupTableData(std::vector<Student*>&& students, std::vector<Discipline*>&& disciplines,
	std::vector<std::vector<AttestationResult*>>&& tableBody) :
	m_students(std::move(students)), m_disciplines(std::move(disciplines)), m_tableBody(std::move(tableBody)) { }

const std::vector<Student*>& GroupTableData::GetStudents() const {
	return m_students;
}

const std::vector<Discipline*>& GroupTableData::GetDisciplines() const {
	return m_disciplines;
}

const std::vector<std::vector<AttestationResult*>>& GroupTableData::GetTableBody() const {
	return m_tableBody;
}

std::vector<int> GroupTableData::StudentAverages() const {
	std::vector<int> studentAverages(m_students.size(), 0);
	for (int i = 0; i < m_students.size(); i++) {
		int k = 0;
		for (int j = 0; j < m_disciplines.size(); j++) {
			if (m_disciplines[j]->GetAttestationType() == Discipline::AttestationType::eExam) {
				studentAverages[i] += m_tableBody[i][j]->ToPercent();
				k += 1;
			}
		}
		if (k != 0) {
			studentAverages[i] /= k;
		}
	}
	return studentAverages;
}

std::vector<int> GroupTableData::DisciplineAverages() const {
	std::vector<int> disciplineAverages(m_disciplines.size(), 0);
	for (int i = 0; i < m_disciplines.size(); i++) {
		for (int j = 0; j < m_students.size(); j++) {
			disciplineAverages[i] += m_tableBody[j][i] ? m_tableBody[j][i]->ToPercent() : 0;
		}
		if (m_students.size() != 0) {
			disciplineAverages[i] /= m_students.size();
		}
	}
	return disciplineAverages;
}

int GroupTableData::GroupAverage() const {
	std::vector<int> studentAverages = StudentAverages();
	int res = 0;
	for (int i = 0; i < m_students.size(); i++) {
		res += studentAverages[i];
	}
	if (m_students.size() == 0) {
		return 0;
	}
	return res / m_students.size();
}
