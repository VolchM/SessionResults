#pragma once

#include "AttestationResult.hpp"

#include <string>


// Результат зачёта
class PassFailExamResult : public AttestationResult
{
private:
	// Получен ли зачёт
	bool m_passed;

public:
	PassFailExamResult(bool passed);

	std::string ToString() const override;
	std::string ToStringCompact() const override;
	int ToPercent() const override;
	bool IsPassed() const override;
	int ToScore() const override;
};
