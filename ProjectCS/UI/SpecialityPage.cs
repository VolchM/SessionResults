using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace SessionResultsCS.UI
{
    public class SpecialityPage : LoopPage
    {
        private Speciality _speciality;

        public SpecialityPage(Speciality speciality)
        {
            _speciality = speciality;
            SetPicker(new MenuActionPicker([
                ("Перейти к группе", GoToGroup),
                ("Перейти к списку дисциплин", GoToDisciplineList),
                ("Изменить код специальности", ChangeSpecialityCode),
                ("Изменить название специальности", ChangeSpecialityName),
                ("Добавить группу", AddGroup),
                ("Удалить группу", DeleteGroup),
                ("Назад", StopLoop),
            ]));
        }

        protected override void Loop()
        {
            Console.WriteLine($"====== {_speciality} ======");
            Console.WriteLine("Группы:");
            PrintGroups();
        }


        private void GoToGroup()
        {
            int selectedIndex = SelectGroup();
            if (selectedIndex != -1)
            {
                new GroupPage(_speciality.GetGroupAt(selectedIndex)).Start();
            }
        }

        private void GoToDisciplineList()
        {
            Console.Write($"Введите курс ({Speciality.MIN_COURSE}-{Speciality.MAX_COURSE}): ");
            string input = Console.ReadLine()!;

            if (int.TryParse(input, out int course) && (course >= Speciality.MIN_COURSE && course <= Speciality.MAX_COURSE))
            {
                new DisciplineListPage(_speciality, course).Start();
            }
            else
            {
                Console.WriteLine("Введен некорректный курс");
            }
        }

        private void ChangeSpecialityCode()
        {
            try
            {
                Console.Write("Введите новый код специальности: ");
                string name = Console.ReadLine()!;
                _speciality.Name = name;
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Введен некорректный код");
            }
        }

        private void ChangeSpecialityName()
        {
            try
            {
                Console.Write("Введите новое название специальности: ");
                string name = Console.ReadLine()!;
                _speciality.Name = name;
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Введено некорректное название");
            }
        }

        private void AddGroup()
        {
            Console.Write("Введите название новой группы: ");
            string name = Console.ReadLine()!;
            Console.Write("Введите курс новой группы: ");
            string course = Console.ReadLine()!;

            try
            {
                Group group = new Group(_speciality, name, int.Parse(course));
                _speciality.AddGroup(group);
            }
            catch (Exception e) when (e is ArgumentException || e is FormatException)
            {
                Console.WriteLine("Не удалось добавить группу");
            }
        }

        private void DeleteGroup()
        {
            int selectedIndex = SelectGroup();
            if (selectedIndex != -1)
            {
                _speciality.DeleteGroup(_speciality.GetGroupAt(selectedIndex));
            }
        }


        private void PrintGroups()
        {
            foreach (var (index, group) in _speciality.GetGroups().Index())
            {
                Console.WriteLine($"{index + 1}. {group}");
            }
        }

        private int SelectGroup()
        {
            Console.Write("Введите номер группы: ");
            string input = Console.ReadLine()!;
            if (int.TryParse(input, out int value) && (value >= 1 && value <= _speciality.GetGroupCount()))
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
