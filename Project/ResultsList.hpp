#pragma once

#include "AttestationResult.hpp"
#include "Student.hpp"
#include "Discipline.hpp"

#include <vector>
#include <algorithm>
#include <numeric>


template<typename T>
requires std::derived_from<T, AttestationResult>
class ResultsList {
private:
	std::vector<std::shared_ptr<T>> m_results;

public:
	ResultsList() : m_results() {}
	ResultsList(const std::vector<std::shared_ptr<T>>& results) : m_results(results) {}
	ResultsList(std::vector<std::shared_ptr<T>>&& results) : m_results(std::move(results)) {}
	ResultsList(const std::vector<std::shared_ptr<Student>>& students, std::shared_ptr<Discipline> discipline) {
		AddStudentsResults(students, discipline);
	}


	void Add(std::shared_ptr<T> result) {
		m_results.push_back(result);
	}

	void AddRange(const std::vector<std::shared_ptr<T>>& results) {
		std::ranges::copy(results, std::back_inserter(m_results));
	}

	void AddStudentsResults(const std::vector<std::shared_ptr<Student>>& students, std::shared_ptr<Discipline> discipline) {
		std::ranges::transform(
			students,
			std::back_inserter(m_results),
			[&](auto& student) {
				return std::dynamic_pointer_cast<T>(student->GetSessionResults().GetResult(discipline));
			}
		);
	}

	int GetSize() const {
		return m_results.size();
	}

	const std::vector<std::shared_ptr<T>>& GetResults() const {
		return m_results;
	}

	int AverageScore() const {
		int sum = std::accumulate(m_results.begin(), m_results.end(), 0,
			[](int acc, auto& res) {
				return acc + (res ? res->ToScore() : 0);
			}
		);
		return m_results.size() == 0 ? 0 : sum / static_cast<int>(m_results.size());
	}

	double PassedPercent() const {
		int sum = std::accumulate(m_results.begin(), m_results.end(), 0,
			[](int acc, auto& res) {
				return acc + ((res != nullptr && res->IsPassed()) ? 1 : 0);
			}
		);
		return m_results.size() == 0 ? 0.0 : 100.0 * sum / m_results.size();
	}
};
