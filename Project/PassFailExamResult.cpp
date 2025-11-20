#include "PassFailExamResult.hpp"


PassFailExamResult::PassFailExamResult(bool passed) {
	m_passed = passed;
}

std::string PassFailExamResult::ToString() {
	return m_passed ? "Зачёт" : "Незачёт";
}

std::string PassFailExamResult::ToStringCompact() {
	return m_passed ? "Зач" : "Нез";
}

int PassFailExamResult::ToPercent() {
	return m_passed ? MAX_PERCENT : 0;
}

bool PassFailExamResult::IsPassed() {
	return m_passed;
}

int PassFailExamResult::ToScore() {
	return ToPercent();
}
