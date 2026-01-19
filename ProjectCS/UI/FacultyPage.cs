using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SessionResultsCS.UI
{
    public class FacultyPage : LoopPage
    {
        private Faculty _faculty;

        public FacultyPage(Faculty faculty)
        {
            _faculty = faculty;
            SetPicker(new MenuActionPicker([
                ("Перейти к специальности", GoToSpeciality),
                ("Изменить название факультета", ChangeFacultyName),
                ("Добавить специальность", AddSpeciality),
                ("Удалить специальность", DeleteSpeciality),
                ("Сохранить изменения и вернуться в главное меню", StopLoop),
            ]));
        }

        protected override void Loop()
        {
            Console.WriteLine($"======== {_faculty} ========");
            Console.WriteLine("Специальности:");
            PrintSpecialities();
        }


        private void GoToSpeciality()
        {
            int selectedIndex = SelectSpeciality();
            if (selectedIndex != -1)
            {
                new SpecialityPage(_faculty.GetSpecialityAt(selectedIndex)).Start();
            }
        }

        private void ChangeFacultyName()
        {
            try
            {
                Console.Write("Введите новое название факультета: ");
                string name = Console.ReadLine()!;
                _faculty.Name = name;
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Введено некорректное название");
            }
        }

        private void AddSpeciality()
        {
            Console.Write("Введите код новой специальности: ");
            string code = Console.ReadLine()!;
            Console.Write("Введите название новой специальности: ");
            string name = Console.ReadLine()!;
            
            try
            {
                Speciality speciality = new Speciality(_faculty, code, name);
                _faculty.AddSpeciality(speciality);
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Не удалось добавить специальность");
            }
        }

        private void DeleteSpeciality()
        {
            int selectedIndex = SelectSpeciality();
            if (selectedIndex != -1)
            {
                _faculty.DeleteSpeciality(_faculty.GetSpecialityAt(selectedIndex));
            }
        }


        private void PrintSpecialities()
        {
            foreach (var (index, speciality) in _faculty.GetSpecialities().Index())
            {
                Console.WriteLine($"{index + 1}. {speciality}");
            }
        }

        private int SelectSpeciality()
        {
            Console.Write("Введите номер специальности: ");
            string input = Console.ReadLine()!;
            if (int.TryParse(input, out int value) && (value >= 1 && value <= _faculty.GetSpecialityCount()))
            {
                return value - 1;
            }
            else
            {
                Console.WriteLine("Введён неверный номер");
                return -1;
            }
        }
    }
}
