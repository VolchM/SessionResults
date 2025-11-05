using System;
using System.Collections.Generic;

namespace SessionResults
{
    // Класс для хранения списка дисциплин
    public class DisciplineList
    {
        public const int DISCIPLINE_NOT_FOUND = -1;


        // Массив дисциплин
        private List<Discipline> _disciplines;


        public DisciplineList()
        {
            _disciplines = new List<Discipline>();
        }

        public DisciplineList(IEnumerable<Discipline> disciplines)
        {
            _disciplines = new List<Discipline>(disciplines);
        }


        // Возвращает количество дисциплин в списке
        public int GetSize()
        {
            return _disciplines.Count;
        }

        // Возвращает дисциплину по указанному индексу
        public Discipline GetDisciplineAt(int index)
        {
            return _disciplines[index];
        }

        // Возвращает массив дисциплин
        public List<Discipline> GetDisciplines()
        {
            return _disciplines;
        }

        // Находит дисциплину и возвращает её индекс. Если такой дисциплины нет в списке возвращает DISCIPLINE_NOT_FOUND
        public int FindDiscipline(Discipline discipline)
        {
            for (int i = 0; i < _disciplines.Count; i++)
            {
                if (_disciplines[i].Equals(discipline))
                {
                    return i;
                }
            }
            return -1;
        }

        // Добавляет дисциплину в список и возвращает true при успешном добавлении, иначе false
        public bool AddDiscipline(Discipline discipline)
        {
            if (FindDiscipline(discipline) != DISCIPLINE_NOT_FOUND)
            {
                return false;
            }
            _disciplines.Add(discipline);
            return true;
        }

        // Убирает дисциплину из списка по индексу
        public void RemoveDisciplineAt(int index)
        {
            _disciplines.RemoveAt(index);
        }

        // Убирает дисциплину из списка и возвращает true при успешном удалении, иначе false
        public bool RemoveDiscipline(Discipline discipline)
        {
            int index = FindDiscipline(discipline);
            if (index == DISCIPLINE_NOT_FOUND)
            {
                return false;
            }
            _disciplines.RemoveAt(index);
            return true;
        }
    }
}
