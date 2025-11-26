#pragma once

#include "Student.hpp"
#include "AttestationResult.hpp"

#include <vector>
#include <memory>


// Данные таблицы группы
class GroupTableData {
public:
	using StudentArray = std::vector<std::shared_ptr<Student>>;
	using DisciplineArray = std::vector<std::shared_ptr<Discipline>>;
	using AttestationResultTable = std::vector<std::vector<std::shared_ptr<AttestationResult>>>;

	static const std::string FIO_COLUMN_HEADER;
	static const std::string AVERAGE_COLUMN_HEADER;
	static const int EXTRA_COLUMNS_COUNT;

private:
	StudentArray m_students;
	DisciplineArray m_disciplines;
	AttestationResultTable m_tableBody;

public:
	GroupTableData(const StudentArray& students, const DisciplineArray& disciplines,
		const AttestationResultTable& tableBody);
	GroupTableData(StudentArray&& students, DisciplineArray&& disciplines,
		AttestationResultTable&& tableBody);
	GroupTableData(const GroupTableData& other);


	// Возвращает массив студентов в порядке вхождения в таблицу
	const StudentArray& GetStudents() const;

	// Возвращает массив дисциплин в порядке вхождения в таблицу
	const DisciplineArray& GetDisciplines() const;
	
	// Возвращает двумерный массив результатов аттестации
	const AttestationResultTable& GetTableBody() const;

	// Возвращает массив средних баллов студентов по экзаменам
	std::vector<int> StudentAverages() const;

	// Возвращает массив средних баллов/процентов сдачи по дисциплинам
	std::vector<int> DisciplineAverages() const;

	// Возвращает средний балл группы по экзаменам
	int GroupAverage() const;


	std::vector<std::string> TableHeader() const;

	std::vector<std::vector<std::string>> TableBodyToStrings(bool compactResults) const;

	std::vector<std::string> TableDisciplineAverages() const;
};
