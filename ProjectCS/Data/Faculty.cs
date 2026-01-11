using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace SessionResultsCS
{
    public class Faculty
    {
        public const int SPECIALITY_NOT_FOUND = -1;


        private string _name;
        // Список специальностей
        private List<Speciality> _specialities;


        // Название факультета
        public string Name
        {
            get { return _name; }
            set
            {
                string newName = value.Trim();
                if (newName.Length == 0)
                {
                    throw new ArgumentException("Faculty name cannot be empty");
                }
                _name = newName;
            }
        }


        public Faculty(string name)
        {
            Name = name;
            _specialities = new List<Speciality>();
        }


        // Возвращает количество специальностей
        public int GetSpecialityCount()
        {
            return _specialities.Count;
        }

        // Возвращает специальность по указанному индексу
        public Speciality GetSpecialityAt(int index)
        {
            return _specialities[index];
        }

        // Возвращает список специальностей
        public ReadOnlyCollection<Speciality> GetSpecialities()
        {
            return _specialities.AsReadOnly();
        }

        // Находит специальность по коду и возвращает её индекс. Если такой специальности нет в списке возвращает SPECIALITY_NOT_FOUND
        public int FindSpecialityByCode(string code)
        {
            return _specialities.FindIndex(speciality => speciality.Code == code);
        }

        // Добавляет специальность
        public void AddSpeciality(Speciality speciality)
        {
            if (FindSpecialityByCode(speciality.Code) != SPECIALITY_NOT_FOUND)
            {
                throw new ArgumentException("Faculty already contains added speciality");
            }
            _specialities.Add(speciality);
        }

        // Удаляет специальность по коду
        public void DeleteSpecialityByCode(string code)
        {
            int index = FindSpecialityByCode(code);
            if (index == SPECIALITY_NOT_FOUND)
            {
                throw new ArgumentException("Faculty doesn't contain deleted speciality");
            }
            _specialities.RemoveAt(index);
        }

        // Удаляет специальность
        public void DeleteSpeciality(Speciality speciality)
        {
            DeleteSpecialityByCode(speciality.Code);
        }
    }
}
