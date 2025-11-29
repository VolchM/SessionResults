#include "GroupTableData.hpp"

const std::string GroupTableData::FIO_COLUMN_HEADER = "ФИО";
const std::string GroupTableData::AVERAGE_COLUMN_HEADER = "Средний балл";
const int GroupTableData::EXTRA_COLUMNS_COUNT = 2;


GroupTableData::GroupTableData(const StudentArray& students, const DisciplineArray& disciplines,
	const AttestationResultTable& tableBody) :
	m_students(students), m_disciplines(disciplines), m_tableBody(tableBody) { }

GroupTableData::GroupTableData(StudentArray&& students, DisciplineArray&& disciplines,
	AttestationResultTable&& tableBody) :
	m_students(std::move(students)), m_disciplines(std::move(disciplines)), m_tableBody(std::move(tableBody)) { }

GroupTableData::GroupTableData(const GroupTableData& other) :
	m_students(other.m_students), m_disciplines(other.m_disciplines), m_tableBody(other.m_tableBody) { }

const GroupTableData::StudentArray& GroupTableData::GetStudents() const {
	return m_students;
}

const GroupTableData::DisciplineArray& GroupTableData::GetDisciplines() const {
	return m_disciplines;
}

const GroupTableData::AttestationResultTable& GroupTableData::GetTableBody() const {
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


std::vector<std::string> GroupTableData::TableHeader() const {
	std::vector<std::string> cells;
	cells.push_back(FIO_COLUMN_HEADER);
	for (int i = 1; i <= m_disciplines.size(); i++) {
		cells.push_back(std::to_string(i));
	}
	cells.push_back(AVERAGE_COLUMN_HEADER);

	return cells;
}

std::vector<std::vector<std::string>> GroupTableData::TableBodyToStrings(bool compactResults) const {
	std::vector<std::vector<std::string>> result;

	std::vector<int> studentAverages = StudentAverages();
	for (int i = 0; i < m_students.size(); i++) {
		std::vector<std::string> cells(m_disciplines.size() + EXTRA_COLUMNS_COUNT);

		cells[0] = m_students[i]->GetLastNameWithInitials();
		for (int j = 0; j < m_disciplines.size(); j++) {
			const std::shared_ptr<AttestationResult>& res = m_tableBody[i][j];
			if (compactResults) {
				cells[j + 1] = res ? res->ToStringCompact() : "";
			} else {
				cells[j + 1] = res ? res->ToString() : "";
			}
		}
		cells.back() = std::to_string(studentAverages[i]);

		result.push_back(cells);
	}

	return result;
}

std::vector<std::string> GroupTableData::TableDisciplineAverages() const {
	std::vector<std::string> cells;
	cells.push_back("");
	for (int average : DisciplineAverages()) {
		cells.push_back(std::to_string(average));
	}
	cells.push_back(std::to_string(GroupAverage()));

	return cells;
}