#pragma once

#include "Data/Student.hpp"

#include <string>
#include <vector>
#include <memory>


// Группа
class Group : public std::enable_shared_from_this<Group> {
	friend class Speciality;

public:
	static const int STUDENT_NOT_FOUND = -1;

private:
	std::string m_name; // Название группы
	int m_course; // Курс обучения
	std::weak_ptr<Speciality> m_speciality; // Специальность группы
	std::vector<std::shared_ptr<Student>> m_students; // Cписок студентов

public:
	Group(const std::string& name, int course);
	Group(const Group& other) = delete;


	std::string ToString() const;

	// Возвращает название группы
	const std::string& GetName() const;

	// Устанавливает название группы
	void SetName(const std::string& value);

	// Возвращает курс обучения
	int GetCourse() const;

	// Устанавливает курс обучения
	void SetCourse(int value);

	// Возвращает специальность группы
	std::weak_ptr<Speciality> GetSpeciality() const;

	// Возвращает список дисциплин группы
	const DisciplineList& GetDisciplineList() const;


	// Возвращает количество студентов в группе
	int GetStudentCount() const;

	// Возвращает студента по указанному индексу
	std::shared_ptr<Student> GetStudentAt(int index) const;

	// Возврашает список студентов
	const std::vector<std::shared_ptr<Student>>& GetStudents() const;

	// Находит студента по номеру студенческго билета и возвращает его индекс. Если такого студента нет в списке возвращает STUDENT_NOT_FOUND
	int FindStudentByID(unsigned int studentID) const;


	// Добавляет студента
	void AddStudent(std::shared_ptr<Student> student);

	// Удаляет студента по номеру студенческого билета
	void DeleteStudentByID(unsigned int studentID);

	// Удаляет студента
	void DeleteStudent(std::shared_ptr<Student> student);
};
