#include "GroupTable/GroupTableData.hpp"

#include <algorithm>
#include <ranges>
#include <numeric>


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


template<std::ranges::range R>
requires std::is_arithmetic_v<std::ranges::range_value_t<R>>
double RangeAverage(R&& r) {
	auto [sum, size] = std::accumulate(
		std::ranges::begin(r),
		std::ranges::end(r),
		std::pair(0.0, 0),
		[](auto acc, auto cur) {
			return std::pair(acc.first + cur, acc.second + 1);
		}
	);
	return size == 0 ? 0.0 : sum / size;
}

std::vector<int> GroupTableData::StudentAverages() const {
	std::vector<int> studentAverages(m_students.size(), 0);

	for (int i = 0; i < m_students.size(); i++) {
		studentAverages[i] = static_cast<int>(RangeAverage(
			std::views::iota(0, static_cast<int>(m_disciplines.size()))
			| std::views::filter([&](int j) { return m_disciplines[j]->GetAttestationType() == Discipline::AttestationType::eExam; })
			| std::views::transform([&](int j) { return m_tableBody[i][j] ? m_tableBody[i][j]->ToScore() : 0; })
		));
	}
	return studentAverages;
}

std::vector<int> GroupTableData::DisciplineAverages() const {
	std::vector<int> disciplineAverages(m_disciplines.size(), 0);
	for (int j = 0; j < m_disciplines.size(); j++) {
		disciplineAverages[j] = static_cast<int>(RangeAverage(
			std::views::iota(0, static_cast<int>(m_students.size()))
			| std::views::transform([&](int i) { return m_tableBody[i][j] ? m_tableBody[i][j]->ToScore() : 0; })
		));
	}
	return disciplineAverages;
}

int GroupTableData::GroupAverage() const {
	return static_cast<int>(RangeAverage(StudentAverages()));
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
		std::vector<std::string> cells;

		cells.push_back(m_students[i]->GetLastNameWithInitials());
		std::ranges::transform(m_tableBody[i],
			std::back_inserter(cells),
			[&](auto& res) {
				if (!res) return std::string();
				return (compactResults ? res->ToStringCompact() : res->ToString());
			}
		);
		cells.push_back(std::to_string(studentAverages[i]));

		result.push_back(std::move(cells));
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