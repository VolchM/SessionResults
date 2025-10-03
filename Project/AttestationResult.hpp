#pragma once

#include <string>


// ����������� ����� - ��������� ����������
class AttestationResult
{
public:
	// ����������� ��������� � ������
	virtual std::string ToString() = 0;

	// ����������� ��������� � ������� ����������
	virtual int ToPercent() = 0;

	// ����������, ����� �� ����������
	virtual bool IsPassed() = 0;
};
