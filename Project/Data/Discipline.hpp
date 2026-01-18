#pragma once

#include <string>


// Дисциплина, по которой производится аттестация
class Discipline
{
public:
	// Перечисление типов аттестации
	enum class AttestationType 
	{ 
		eExam,			// Экзамен
		ePassFailExam	// Зачёт
	};

private:
	std::string m_name; // Название дисциплины
	AttestationType m_attestationType; // Тип аттестации

public:
	Discipline(std::string name, AttestationType attestationType);
	Discipline(const Discipline& other);


	std::string ToString() const;

	// Возвращает название дисциплины
	const std::string& GetName() const;

	// Возвращает тип аттестации
	AttestationType GetAttestationType() const;

	// Проверяет равенство с другой дисциплин
	bool Equals(const Discipline& other) const;

	bool operator==(const Discipline& other);

	bool operator!=(const Discipline& other);
};
