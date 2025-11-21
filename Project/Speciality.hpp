#pragma once

#include "DisciplineList.hpp"
#include "Group.hpp"

#include <string>
#include <vector>
#include <memory>


class Speciality : public std::enable_shared_from_this<Speciality> {
public:
	static const int MIN_COURSE = 1;
	static const int MAX_COURSE = 4;

	static const int GROUP_NOT_FOUND = -1;

private:
	std::string m_code; // Код специальности
	std::string m_name; // Название специальности
	DisciplineList m_disciplines[MAX_COURSE]; // Список дисциплин на каждом курсе
	std::vector<std::shared_ptr<Group>> m_groups; // Список групп

public:
	Speciality(const std::string& code, const std::string& name);


	// Возвращает код специальности
	const std::string& GetCode() const;

	// Устанавливает код специальности
	void SetCode(const std::string& value);

	// Возвращает название специальности
	const std::string& GetName() const;

	// Устанавливает название специальности
	void SetName(const std::string& value);

	// Возвращает список дисциплин курса для чтения и изменения
	DisciplineList& GetDisciplineList(int course);

	// Возвращает список дисциплин курса для чтения
	const DisciplineList& GetDisciplineList(int course) const;


	// Возвращает количество групп специальности
	int GetGroupCount() const;

	// Возвращает группу по указанному индексу
	std::shared_ptr<Group> GetGroupAt(int index) const;

	// Возвращает список групп
	const std::vector<std::shared_ptr<Group>>& GetGroups() const;

	// Находит группу по названию и возвращает её индекс. Если такой группы нет в списке возвращает GROUP_NOT_FOUND
	int FindGroupByName(const std::string& name) const;


	// Добавляет группу
	void AddGroup(std::shared_ptr<Group> group);

	// Удаляет группу по названию
	void DeleteGroupByName(const std::string& name);

	// Удаляет группу
	void DeleteGroup(std::shared_ptr<Group> group);
};
