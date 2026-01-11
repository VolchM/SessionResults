using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace SessionResultsCS
{
    public class Speciality
    {
        public const int MIN_COURSE = 1;
        public const int MAX_COURSE = 4;
        public const int GROUP_NOT_FOUND = -1;


        private string _code;
        private string _name;
        // Список групп
        private List<Group> _groups;
        // Список дисциплин на каждом курсе
        private DisciplineList[] _disciplines;


        // Количество существующих объектов специальностей
        public static int InstanceCount { get; private set; } = 0;


        // Код специальности
        public string Code
        {
            get { return _code; }
            set
            {
                if (value.Contains(' ') || value.Length == 0)
                {
                    throw new ArgumentException("Speciality code cannot contain spaces or be empty");
                }
                _code = value;
            }
        }

        // Название специальности
        public string Name
        {
            get { return _name; }
            set
            {
                string newName = value.Trim();
                if (newName.Length == 0)
                {
                    throw new ArgumentException("Speciality name cannot be empty");
                }
                _name = newName;
            }
        }


        public Speciality(string code, string name)
        {
            Code = code;
            Name = name;
            _groups = new List<Group>();
            _disciplines = new DisciplineList[MAX_COURSE - MIN_COURSE + 1];
            for (int i = 0; i < MAX_COURSE - MIN_COURSE + 1; i++)
            {
                _disciplines[i] = new DisciplineList();
            }
            InstanceCount++;
        }

        ~Speciality()
        {
            InstanceCount--;
        }


        // Возвращает список дисциплин курса для чтения и изменения
        public DisciplineList GetDisciplineList(int course)
        {
            if (!(course >= Speciality.MIN_COURSE && course <= Speciality.MAX_COURSE))
            {
                throw new ArgumentException("Invalid course value");
            }
            return _disciplines[course - MIN_COURSE];
        }

        // Возвращает количество групп специальности
        public int GetGroupCount()
        {
            return _groups.Count;
        }

        // Возвращает группу по указанному индексу
        public Group GetGroupAt(int index)
        {
            return _groups[index];
        }

        // Возвращает список групп
        public ReadOnlyCollection<Group> GetGroups()
        {
            return _groups.AsReadOnly();
        }

        // Находит группу по названию и возвращает её индекс. Если такой группы нет в списке возвращает GROUP_NOT_FOUND
        public int FindGroupByName(string name)
        {
            return _groups.FindIndex(group => group.Name == name);
        }

        // Добавляет группу
        public void AddGroup(Group group)
        {
            if (FindGroupByName(group.Name) != GROUP_NOT_FOUND)
            {
                throw new ArgumentException("Speciality already contains added group");
            }
            _groups.Add(group);
        }

        // Удаляет группу по названию
        public void DeleteGroupByName(string name)
        {
            int index = FindGroupByName(name);
            if (index == GROUP_NOT_FOUND)
            {
                throw new ArgumentException("Speciality doesn't contain deleted group");
            }
            _groups.RemoveAt(index);
        }

        // Удаляет группу
        public void DeleteGroup(Group group)
        {
            DeleteGroupByName(group.Name);
        }
    }
}
