#pragma once

#include "AttestationResult.hpp"

#include <string>


// ��������� ��������
class ExamResult : public AttestationResult
{
private:
	// ���������� ���� �� �������
	int m_score;

public:
	ExamResult(int score);

	std::string ToString() override;
	int ToPercent() override;
	bool IsPassed() override;
};
