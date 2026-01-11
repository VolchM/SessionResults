using System;
using System.Collections.Generic;

namespace SessionResultsCS
{
    public class SessionResults
    {
        // Список дисциплин, по которым получены результаты
        private DisciplineList _disciplines;

        // Список полученных результатов
        private List<AttestationResult> _results;


        public SessionResults()
        {
            _disciplines = new DisciplineList();
            _results = new List<AttestationResult>();
        }


        // Возвращает результат по дисциплине либо null, если по этой дисциплине результата нет
        public AttestationResult? GetResult(Discipline discipline)
        {
            int index = _disciplines.FindDiscipline(discipline);
            if (index == DisciplineList.DISCIPLINE_NOT_FOUND)
            {
                return null;
            }
            return _results[index];
        }

        // Устанавливает результат по дисциплине
        public void SetResult(Discipline discipline, AttestationResult result)
        {
            int index = _disciplines.FindDiscipline(discipline);
            if (index == DisciplineList.DISCIPLINE_NOT_FOUND)
            {
                _disciplines.AddDiscipline(discipline);
                _results.Add(result);
            }
            else
            {
                _results[index] = result;
            }
        }

        // Удаляет результат по дисциплине
        public void DeleteResult(Discipline discipline)
        {
            int index = _disciplines.FindDiscipline(discipline);
            if (index != DisciplineList.DISCIPLINE_NOT_FOUND)
            {
                _disciplines.RemoveDisciplineAt(index);
                _results.RemoveAt(index);
            }
        }

    }
}
