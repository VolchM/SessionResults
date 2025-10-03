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

	std::string ToString() override;
	int ToPercent() override;
	bool IsPassed() override;
};
