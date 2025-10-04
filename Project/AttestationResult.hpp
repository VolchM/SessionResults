#pragma once

#include <string>


// Абстрактный класс - Результат аттестации
class AttestationResult
{
public:
	// Преобразует результат в строку
	virtual std::string ToString() = 0;

	// Преобразует результат в процент выполнения
	virtual int ToPercent() = 0;

	// Возвращает, сдана ли аттестация
	virtual bool IsPassed() = 0;
};
