#include "PassFailExamResult.hpp"


PassFailExamResult::PassFailExamResult(bool passed) {
	m_passed = passed;
}

std::string PassFailExamResult::ToString() {
	return m_passed ? "Зачёт" : "Незачёт";
}

int PassFailExamResult::ToPercent() {
	return m_passed ? 100 : 0;
}

bool PassFailExamResult::IsPassed() {
	return m_passed;
}
