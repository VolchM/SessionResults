using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace SessionResultsCS
{
    // Класс для хранения списка дисциплин
    public class DisciplineList: IEnumerable<Discipline>
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


        public DisciplineList ShallowClone()
        {
            return new DisciplineList(_disciplines);
        }

        public DisciplineList DeepClone()
        {
            DisciplineList disciplineList = new DisciplineList();
            foreach (Discipline discipline in _disciplines)
            {
                disciplineList.AddDiscipline(discipline.Clone());
            }
            return disciplineList;
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
        public ReadOnlyCollection<Discipline> GetDisciplines()
        {
            return _disciplines.AsReadOnly();
        }

        // Находит дисциплину и возвращает её индекс. Если такой дисциплины нет в списке возвращает DISCIPLINE_NOT_FOUND
        public int FindDiscipline(Discipline discipline)
        {
            return _disciplines.IndexOf(discipline);
        }

        // Находит дисциплину по названию и возвращает её индекс. Если такой дисциплины нет в списке возвращает DISCIPLINE_NOT_FOUND
        public int FindDisciplineByName(string name)
        {
            return _disciplines.FindIndex(discipline => discipline.Name == name);
        }

        public IEnumerator<Discipline> GetEnumerator()
        {
            return _disciplines.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }


        // Добавляет дисциплину в список
        public void AddDiscipline(Discipline discipline)
        {
            if (FindDiscipline(discipline) != DISCIPLINE_NOT_FOUND)
            {
                throw new ArgumentException("Added discipline is already in list");
            }
            _disciplines.Add(discipline);
        }

        // Убирает дисциплину из списка по индексу
        public void RemoveDisciplineAt(int index)
        {
            _disciplines.RemoveAt(index);
        }

        // Убирает дисциплину из списка
        public void RemoveDiscipline(Discipline discipline)
        {
            int index = FindDiscipline(discipline);
            if (index == DISCIPLINE_NOT_FOUND)
            {
                throw new ArgumentException("Deleted discipline is not in list");
            }
            _disciplines.RemoveAt(index);
        }
    }
}
