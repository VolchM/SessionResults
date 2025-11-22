#pragma once

#include <string>
#include <iostream>


// Абстрактный класс - Результат аттестации
class AttestationResult
{
public:
	static const int MAX_PERCENT = 100;

	// Преобразует результат в строку
	virtual std::string ToString() const = 0;

	// Преобразует результат в короткую строку
	virtual std::string ToStringCompact() const = 0;

	// Преобразует результат в процент выполнения
	virtual int ToPercent() const = 0;

	// Возвращает, сдана ли аттестация
	virtual bool IsPassed() const = 0;

	// Возвращает балл для расчёта среднего балла
	virtual int ToScore() const = 0;


	// Сравнивают объекты на основе процента выполнения
	bool operator==(const AttestationResult& other);
	bool operator!=(const AttestationResult& other);
	bool operator<(const AttestationResult& other);
	bool operator<=(const AttestationResult& other);
	bool operator>(const AttestationResult& other);
	bool operator>=(const AttestationResult& other);
};

std::ostream& operator<<(std::ostream& os, const AttestationResult& res);
