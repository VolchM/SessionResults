#pragma once

#include "AttestationResult.hpp"
#include "ExamResult.hpp"
#include "PassFailExamResult.hpp"
#include "Discipline.hpp"
#include "DisciplineReferenceList.hpp"

#include <vector>


// Результаты сессии
class SessionResults {
private:
	DisciplineReferenceList m_disciplines; // Список дисциплин, по которым получены результаты
	std::vector<AttestationResult*> m_results; // Список полученных результатов

public:
	SessionResults();
	~SessionResults();


	// Возвращает результат по дисциплине
	AttestationResult* GetResult(Discipline* discipline);

	// Устанавливает результат по дисциплине
	void SetResult(Discipline* discipline, AttestationResult* result);

	// Удаляет результат по дисциплине
	void DeleteResult(Discipline* discipline);
};
