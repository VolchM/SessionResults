#pragma once

#include "Discipline.hpp"

#include <vector>
#include <memory>


// Класс для хранения списка ссылок на дисциплины
class DisciplineList {
public:
	static const int DISCIPLINE_NOT_FOUND = -1;

private:
	std::vector<std::shared_ptr<Discipline>> m_disciplines; // массив указателей на дисциплины

public:
	DisciplineList();
	DisciplineList(const std::vector<std::shared_ptr<Discipline>>& disciplines);

	// Возвращает количество дисциплин в списке
	int GetSize() const;

	// Возвращает дисциплину по указанному индексу
	std::shared_ptr<Discipline> GetDisciplineAt(int index) const;
	
	// Возвращает массив указателей на дисциплины
	const std::vector<std::shared_ptr<Discipline>>& GetDisciplines() const;

	// Находит дисциплину и возвращает её индекс. Если такой дисциплины нет в списке возвращает DISCIPLINE_NOT_FOUND
	int FindDiscipline(std::shared_ptr<Discipline> discipline) const;

	
	// Добавляет дисциплину в список и возвращает true при успешном добавлении, иначе false
	bool AddDiscipline(std::shared_ptr<Discipline> discipline);

	// Убирает дисциплину по индексу
	void RemoveDisciplineAt(int index);

	// Убирает дисциплину из списка и возвращает true при успешном удалении, иначе false
	bool RemoveDiscipline(std::shared_ptr<Discipline> discipline);
};
