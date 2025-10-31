#include "ExamResult.hpp"

#include <stdexcept>


ExamResult::ExamResult(int score) {
	if (score < MIN_SCORE || score > MAX_SCORE) {
		throw std::invalid_argument("Invalid score value");
	}
	m_score = score;
}

std::string ExamResult::ToString() {
	return std::to_string(m_score);
}

std::string ExamResult::ToStringCompact() {
	return std::to_string(m_score);
}

int ExamResult::ToPercent() {
	return ((m_score - MIN_SCORE) * MAX_PERCENT / (MAX_SCORE - MIN_SCORE));
}

bool ExamResult::IsPassed() {
	return m_score >= PASS_SCORE;
}

int ExamResult::ToScore() {
	return m_score;
}
