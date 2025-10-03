#pragma once

#include "AttestationResult.hpp"

#include <string>


// Результат экзамена
class ExamResult : public AttestationResult
{
private:
	// Полученный балл за экзамен
	int m_score;

public:
	ExamResult(int score);

	std::string ToString() override;
	int ToPercent() override;
	bool IsPassed() override;
};
