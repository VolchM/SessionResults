#pragma once

#include "Data/Speciality.hpp"

#include <memory>
#include <string>
#include <vector>


// Факультет
class Faculty : public std::enable_shared_from_this<Faculty>
{
	static const int SPECIALITY_NOT_FOUND = -1;

private:
	std::string m_name; // Название факультета
	std::vector<std::shared_ptr<Speciality>> m_specialities; // Список специальностей

public:
	Faculty(const std::string& name);
	Faculty(const Faculty& other) = delete;


	std::string ToString() const;

	// Возвращает название факультета
	const std::string& GetName() const;

	// Устанавливает название факультета
	void SetName(const std::string& value);


	// Возвращает количество специальностей факультета
	int GetSpecialityCount() const;

	// Возвращает специальность по указанному индексу
	std::shared_ptr<Speciality> GetSpecialityAt(int index) const;

	// Возвращает список специальностей
	const std::vector<std::shared_ptr<Speciality>>& GetSpecialities() const;

	// Находит специальность по коду и возвращает её индекс. Если такой специальности нет в списке возвращает SPECIALITY_NOT_FOUND
	int FindSpecialityByCode(const std::string& code) const;


	// Добавляет специальность
	void AddSpeciality(std::shared_ptr<Speciality> Speciality);

	// Удаляет специальность по коду
	void DeleteSpecialityByCode(const std::string& code);

	// Удаляет специальность
	void DeleteSpeciality(std::shared_ptr<Speciality> Speciality);
};
