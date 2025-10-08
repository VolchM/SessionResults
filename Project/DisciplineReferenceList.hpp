#pragma once

#include "Discipline.hpp"

#include <vector>


// Класс для хранения списка ссылок на дисциплины
class DisciplineReferenceList {
private:
	std::vector<Discipline*> m_disciplines; // массив указателей на дисциплины

public:
	DisciplineReferenceList();
	DisciplineReferenceList(const std::vector<Discipline*>& disciplines);

	// Возвращает количество дисциплин в списке
	int GetSize() const;

	// Возвращает дисциплину по указанному индексу
	Discipline* GetDisciplineAt(int index) const;
	
	// Возвращает массив указателей на дисциплины
	const std::vector<Discipline*>& GetDisciplines() const;

	// Находит дисциплину и возвращает её индекс. Если такой дисциплины нет в списке возвращает -1
	int FindDiscipline(Discipline* discipline) const;

	
	// Добавляет дисциплину
	void AddDiscipline(Discipline* discipline);

	// Убирает дисциплину по индексу
	void RemoveDisciplineAt(int index);

	// Убирает дисциплину
	void RemoveDiscipline(Discipline* discipline);
};
