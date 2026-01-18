#pragma once

#include "Data/Discipline.hpp"

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
	DisciplineList(const DisciplineList& other);

	DisciplineList ShallowClone() const;
	DisciplineList DeepClone() const;

	// Возвращает количество дисциплин в списке
	int GetSize() const;

	// Возвращает дисциплину по указанному индексу
	std::shared_ptr<Discipline> GetDisciplineAt(int index) const;
	
	// Возвращает массив указателей на дисциплины
	const std::vector<std::shared_ptr<Discipline>>& GetDisciplines() const;

	// Находит дисциплину и возвращает её индекс. Если такой дисциплины нет в списке возвращает DISCIPLINE_NOT_FOUND
	int FindDiscipline(std::shared_ptr<Discipline> discipline) const;

	
	// Добавляет дисциплину в список
	void AddDiscipline(std::shared_ptr<Discipline> discipline);

	// Убирает дисциплину по индексу
	void RemoveDisciplineAt(int index);

	// Убирает дисциплину из списка
	void RemoveDiscipline(std::shared_ptr<Discipline> discipline);
};
