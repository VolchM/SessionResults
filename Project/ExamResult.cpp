#include "ExamResult.hpp"

#include <stdexcept>


ExamResult::ExamResult(int score) {
	if (score < 0 || score > 100) {
		throw std::invalid_argument("Score must be between 0 and 100");
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
	return m_score;
}

bool ExamResult::IsPassed() {
	return m_score >= 25;
}

int ExamResult::ToScore() {
	return m_score;
}
