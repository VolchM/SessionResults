#include "AttestationResult.hpp"


bool AttestationResult::operator==(const AttestationResult& other) {
	return this->ToPercent() == other.ToPercent();
}

bool AttestationResult::operator!=(const AttestationResult& other) {
	return this->ToPercent() != other.ToPercent();
}

bool AttestationResult::operator<(const AttestationResult& other) {
	return this->ToPercent() < other.ToPercent();
}

bool AttestationResult::operator<=(const AttestationResult& other) {
	return this->ToPercent() <= other.ToPercent();
}

bool AttestationResult::operator>(const AttestationResult& other) {
	return this->ToPercent() > other.ToPercent();
}

bool AttestationResult::operator>=(const AttestationResult& other) {
	return this->ToPercent() >= other.ToPercent();
}

std::ostream& operator<<(std::ostream& os, const AttestationResult& res) {
	os << res.ToString();
	return os;
}
