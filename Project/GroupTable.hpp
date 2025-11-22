#pragma once

#include "Group.hpp"
#include "Discipline.hpp"
#include "GroupTableData.hpp"
#include "DisciplineList.hpp"

#include <vector>
#include <string>


// Таблица успеваемости студентов одной группы
class GroupTable {
public:
	// Перечисление порядков сортировки
	enum class SortOrder
	{
		eAscending,	// По возрастанию
		eDescending	// По убыванию
	};

private:
	std::shared_ptr<Group> m_group; // Группа
	bool m_includeOnlyFailing; // Включить только неуспевающих студентов
	DisciplineList m_disciplines; // Cписок дисциплин, по которым составляется таблица
	SortOrder m_sortOrder; // Выбранный порядок сортировки
	std::shared_ptr<Discipline> m_sortColumn; // Выбранная дисциплина для сортировки, либо средний балл

public:
	GroupTable(std::shared_ptr<Group> group, bool includeOnlyFailing = false);
	GroupTable(const GroupTable& other);


	// Возвращает группу, по которой сформирована таблица
	std::shared_ptr<Group> GetGroup() const;

	// Возвращает, включены ли только неуспевающие студенты
	bool GetIncludeOnlyFailing() const;

	// Устанавливает, включать ли только неуспевающие студенты
	void SetIncludeOnlyFailing(bool value);

	// Возвращает список дисциплин для чтения
	DisciplineList& GetDisciplineList();

	// Возвращает список дисциплин для чтения и изменения
	const DisciplineList& GetDisciplineList() const;

	// Устанавливает список дисциплин
	void SetDisciplineList(const DisciplineList& disciplines);

	// Устанавливает список дисциплин
	void SetDisciplineList(const std::vector<std::shared_ptr<Discipline>>& disciplines);

	// Сортирует студентов по результатам дисциплины
	void SortByDiscipline(std::shared_ptr<Discipline> discipline, SortOrder sortOrder);

	// Сортирует студентов по среднему баллу
	void SortByAverage(SortOrder sortOrder);


	// Создает и возвращает данные таблицы
	GroupTableData GetTableData() const;
};
