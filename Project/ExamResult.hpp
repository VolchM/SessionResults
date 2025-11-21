#pragma once

#include "AttestationResult.hpp"

#include <string>


// Результат экзамена
class ExamResult : public AttestationResult
{
public:
	static const int MIN_SCORE = 0;
	static const int MAX_SCORE = 100;
	static const int PASS_SCORE = 25;

private:
	// Полученный балл за экзамен
	int m_score;

public:
	ExamResult(int score);

	std::string ToString() const override;
	std::string ToStringCompact() const override;
	int ToPercent() const override;
	bool IsPassed() const override;
	int ToScore() const override;
};
