#pragma once

#include "Group.hpp"
#include "DisciplineReferenceList.hpp"
#include "Discipline.hpp"
#include "GroupTableData.hpp"

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
	Group* m_group; // Группа
	bool m_includeOnlyFailing; // Включить только неуспевающих студентов
	DisciplineReferenceList m_disciplines; // Cписок дисциплин, по которым составляется таблица
	SortOrder m_sortOrder; // Выбранный порядок сортировки
	Discipline* m_sortColumn; // Выбранная дисциплина для сортировки, либо средний балл

public:
	GroupTable(Group* group, bool includeOnlyFailing = false);


	// Возвращает группу, по которой сформирована таблица
	Group* GetGroup() const;

	// Возвращает, включены ли только неуспевающие студенты
	bool GetIncludeOnlyFailing() const;

	// Устанавливает, включать ли только неуспевающие студенты
	void SetIncludeOnlyFailing(bool value);

	// Возвращает список дисциплин для чтения
	DisciplineReferenceList& GetDisciplineReferenceList();

	// Возвращает список дисциплин для чтения и изменения
	const DisciplineReferenceList& GetDisciplineReferenceList() const;

	// Устанавливает список дисциплин
	void SetDisciplineReferenceList(const DisciplineReferenceList& disciplines);

	// Устанавливает список дисциплин
	void SetDisciplineReferenceList(const std::vector<Discipline*>& disciplines);

	// Сортирует студентов по результатам дисциплины
	void SortByDiscipline(Discipline* discipline, SortOrder sortOrder);

	// Сортирует студентов по среднему баллу
	void SortByAverage(SortOrder sortOrder);


	// Создает и возвращает данные таблицы
	GroupTableData GetTableData() const;
};
