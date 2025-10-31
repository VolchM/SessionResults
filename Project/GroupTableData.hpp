#pragma once

#include "Student.hpp"
#include "AttestationResult.hpp"

#include <vector>


// Данные таблицы группы
class GroupTableData {
private:
	std::vector<Student*> m_students;
	std::vector<Discipline*> m_disciplines;
	std::vector<std::vector<AttestationResult*>> m_tableBody;

public:
	GroupTableData(const std::vector<Student*>& students, const std::vector<Discipline*>& disciplines,
		const std::vector<std::vector<AttestationResult*>>& tableBody);
	GroupTableData(std::vector<Student*>&& students, std::vector<Discipline*>&& disciplines,
		std::vector<std::vector<AttestationResult*>>&& tableBody);


	// Возвращает массив студентов в порядке вхождения в таблицу
	const std::vector<Student*>& GetStudents() const;

	// Возвращает массив дисциплин в порядке вхождения в таблицу
	const std::vector<Discipline*>& GetDisciplines() const;
	
	// Возвращает двумерный массив результатов аттестации
	const std::vector<std::vector<AttestationResult*>>& GetTableBody() const;

	// Возвращает массив средних баллов студентов по экзаменам
	std::vector<int> StudentAverages() const;

	// Возвращает массив средних баллов/процентов сдачи по дисциплинам
	std::vector<int> DisciplineAverages() const;

	// Возвращает средний балл группы по экзаменам
	int GroupAverage() const;
};
