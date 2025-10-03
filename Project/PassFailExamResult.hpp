#pragma once

#include "AttestationResult.hpp"

#include <string>


// ��������� ������
class PassFailExamResult : public AttestationResult
{
private:
	// ������� �� �����
	bool m_passed;

public:
	PassFailExamResult(bool passed);

	std::string ToString() override;
	int ToPercent() override;
	bool IsPassed() override;
};
