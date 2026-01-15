#pragma once

#include "Data/SessionResults.hpp"

#include <string>
#include <memory>


// Студент
class Student : public std::enable_shared_from_this<Student> {
	friend class Group;

private:
	unsigned int m_studentID; // Номер студенческого билета
	std::string m_firstName; // Имя
	std::string m_lastName; // Фамилия
	std::string m_middleName; // Отчество
	std::weak_ptr<Group> m_group; // Группа
	SessionResults m_sessionResults; // Результаты сессии

public:
	Student(unsigned int studentID, const std::string& firstName, const std::string& lastName, const std::string& middleName);
	Student(const Student& other) = delete;


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

	// Возвращает фамилию и инициалы
	std::string GetLastNameWithInitials() const;

	// Возвращает группу студента
	std::weak_ptr<Group> GetGroup() const;

	// Возвращает результаты сессии для чтения и изменения
	SessionResults& GetSessionResults();
};
