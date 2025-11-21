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


	// Возвращает название дисциплины
	const std::string& GetName() const;

	// Устанавливает название дисциплины
	void SetName(const std::string& value);

	// Возвращает тип аттестации
	AttestationType GetAttestationType() const;

	// Устанавливает тип аттестации
	void SetAttestationType(AttestationType value);

	// Проверяет равенство с другой дисциплин
	bool Equals(const Discipline& other) const;

	bool operator==(const Discipline& other);

	bool operator!=(const Discipline& other);
};
