#pragma once

#include "AttestationResult.hpp"
#include "ExamResult.hpp"
#include "PassFailExamResult.hpp"
#include "Discipline.hpp"
#include "DisciplineList.hpp"

#include <vector>
#include <memory>


// Результаты сессии
class SessionResults {
private:
	DisciplineList m_disciplines; // Список дисциплин, по которым получены результаты
	std::vector<std::shared_ptr<AttestationResult>> m_results; // Список полученных результатов

public:
	SessionResults();


	// Возвращает результат по дисциплине
	std::shared_ptr<AttestationResult> GetResult(std::shared_ptr<Discipline> discipline);

	// Устанавливает результат по дисциплине
	void SetResult(std::shared_ptr<Discipline> discipline, std::shared_ptr<AttestationResult> result);

	// Удаляет результат по дисциплине
	void DeleteResult(std::shared_ptr<Discipline> discipline);
};
