#pragma once

#include "Discipline.hpp"
#include "DisciplineReferenceList.hpp"

#include <vector>


// Класс для хранения списка дисциплин
class DisciplineList {
private:
	std::vector<Discipline*> m_disciplines; // Массив дисциплин

public:
	DisciplineList();
	~DisciplineList();

	// Возвращает количество дисциплин в списке
	int GetSize() const;

	// Проверяет, содержится ли дисциплина в списке
	bool ContainsDiscipline(Discipline* discipline) const;

	// Возвращает массив указателей на дисциплины
	const std::vector<Discipline*>& GetDisciplines() const;

	// Возвращает новый объект класса DisciplineReferenceList, хранящий список ссылок на дисциплины
	DisciplineReferenceList GetDisciplineReferenceList() const;


	// Добавляет дисциплину
	void AddDiscipline(Discipline* discipline);

	// Удаляет дисциплину
	void DeleteDiscipline(Discipline* discipline);
};
