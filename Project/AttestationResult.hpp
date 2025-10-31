#pragma once

#include <string>


// Абстрактный класс - Результат аттестации
class AttestationResult
{
public:
	static const int MAX_PERCENT = 100;

	// Преобразует результат в строку
	virtual std::string ToString() = 0;

	// Преобразует результат в короткую строку
	virtual std::string ToStringCompact() = 0;

	// Преобразует результат в процент выполнения
	virtual int ToPercent() = 0;

	// Возвращает, сдана ли аттестация
	virtual bool IsPassed() = 0;

	// Возвращает балл для расчёта среднего балла
	virtual int ToScore() = 0;
};
