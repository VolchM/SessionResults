#pragma once

#include "Student.hpp"

#include <string>
#include <vector>


class Speciality;

// Группа
class Group {
public:
	static const int STUDENT_NOT_FOUND = -1;

private:
	std::string m_name; // Название группы
	int m_course; // Курс обучения
	Speciality* m_speciality; // Специальность группы
	std::vector<Student*> m_students; // Cписок студентов

public:
	Group(Speciality* speciality, const std::string& name, int course);
	~Group();


	// Возвращает название группы
	const std::string& GetName() const;

	// Устанавливает название группы
	void SetName(const std::string& value);

	// Возвращает курс обучения
	int GetCourse() const;

	// Устанавливает курс обучения
	void SetCourse(int value);

	// Возвращает специальность группы
	Speciality* GetSpeciality() const;


	// Возвращает количество студентов в группе
	int GetStudentCount() const;

	// Возвращает студента по указанному индексу
	Student* GetStudentAt(int index) const;

	// Возврашает список студентов
	const std::vector<Student*>& GetStudents() const;

	// Находит студента по номеру студенческго билета и возвращает его индекс. Если такого студента нет в списке возвращает STUDENT_NOT_FOUND
	int FindStudentByID(unsigned int studentID) const;


	// Добавляет студента
	void AddStudent(Student* student);

	// Удаляет студента по номеру студенческого билета
	void DeleteStudentByID(unsigned int studentID);

	// Удаляет студента
	void DeleteStudent(Student* student);
};
