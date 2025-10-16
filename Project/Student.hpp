#pragma once

#include "SessionResults.hpp"

#include <string>


class Group;

// Студент
class Student {
private:
	unsigned int m_studentID; // Номер студенческого билета
	std::string m_firstName; // Имя
	std::string m_lastName; // Фамилия
	std::string m_middleName; // Отчество
	Group* m_group; // Группа
	SessionResults m_sessionResults; // Результаты сессии

public:
	Student(Group* group, unsigned int studentID, const std::string& firstName, const std::string& lastName, const std::string& middleName);


	// Возвращает номер студенческого билета
	unsigned int GetStudentID() const;

	// Устанавливает номер студенческого билета
	void SetStudentID(unsigned int value);

	// Возвращает имя
	const std::string& GetFirstName() const;

	// Устанавливает имя
	void SetFirstName(const std::string& value);

	// Возвращает фамилию
	const std::string& GetLastName() const;

	// Устанавливает фамилию
	void SetLastName(const std::string& value);

	// Возвращает отчество
	const std::string& GetMiddleName() const;

	// Устанавливает отчество
	void SetMiddleName(const std::string& value);

	// Возвращает полное имя (фамилию, имя и отчество)
	std::string GetFullName() const;

	// Возвращает группу студента
	Group* GetGroup() const;

	// Возвращает результаты сессии для чтения и изменения
	SessionResults& GetSessionResults();
};
