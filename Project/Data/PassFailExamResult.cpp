#include "Data/PassFailExamResult.hpp"


PassFailExamResult::PassFailExamResult(bool passed) {
	m_passed = passed;
}

PassFailExamResult::PassFailExamResult(const PassFailExamResult& other): m_passed(other.m_passed) {}

std::string PassFailExamResult::ToString() const {
	return m_passed ? "Зачёт" : "Незачёт";
}

std::string PassFailExamResult::ToStringCompact() const {
	return m_passed ? "Зач" : "Нез";
}

int PassFailExamResult::ToPercent() const {
	return m_passed ? MAX_PERCENT : 0;
}

bool PassFailExamResult::IsPassed() const {
	return m_passed;
}

int PassFailExamResult::ToScore() const {
	return ToPercent();
}
