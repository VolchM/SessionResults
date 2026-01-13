using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SessionResultsCS.UI
{
    public class GroupPage : LoopPage
    {
        private Group _group;

        private MenuActionPicker _picker;


        public GroupPage(Group group)
        {
            _group = group;
            _picker = new MenuActionPicker([
                ("Перейти к студенту", GoToStudent),
                ("Изменить название группы", ChangeGroupName),
                ("Изменить курс группы", ChangeGroupCourse),
                ("Добавить студента", AddStudent),
                ("Удалить студента", DeleteStudent),
                ("Назад", StopLoop),
            ]);
        }

        protected override void Loop() 
        {
            Console.WriteLine($"==== {_group} ====");
            Console.WriteLine("Студенты:");
            PrintStudents();
            Console.WriteLine("Действия:");
            _picker.PickAndRun();
        }


        private void GoToStudent()
        {
            int selectedIndex = SelectStudent();
            if (selectedIndex != -1)
            {
                new StudentPage(_group.GetStudentAt(selectedIndex)).Start();
            }
        }

        private void ChangeGroupName()
        {
            try
            {
                Console.Write("Введите новое название группы: ");
                string name = Console.ReadLine()!;
                _group.Name = name;
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Введено некорректное название");
            }
        }

        private void ChangeGroupCourse()
        {
            try
            {
                Console.Write("Введите новый курс группы: ");
                string course = Console.ReadLine()!;
                _group.Course = int.Parse(course);
            }
            catch (Exception e) when (e is ArgumentException || e is FormatException)
            {
                Console.WriteLine("Введен некорректный курс");
            }
        }

        private void AddStudent()
        {
            Console.Write("Введите номер студенческого билета нового студента: ");
            string studentID = Console.ReadLine()!;
            Console.Write("Введите имя нового студента: ");
            string firstName = Console.ReadLine()!;
            Console.Write("Введите фамилию нового студента: ");
            string lastName = Console.ReadLine()!;
            Console.Write("Введите отчество нового студента: ");
            string middleName = Console.ReadLine()!;

            try
            {
                Student student = new Student(_group, uint.Parse(studentID), firstName, lastName, middleName);
                _group.AddStudent(student);
            }
            catch (Exception e) when (e is ArgumentException || e is FormatException)
            {
                Console.WriteLine("Не удалось добавить студента");
            }
        }

        private void DeleteStudent()
        {
            int selectedIndex = SelectStudent();
            if (selectedIndex != -1)
            {
                _group.DeleteStudent(_group.GetStudentAt(selectedIndex));
            }
        }


        private void PrintStudents()
        {
            foreach (var (index, student) in _group.GetStudents().Index())
            {
                Console.WriteLine($"{index + 1}. {student}");
            }
        }

        private int SelectStudent()
        {
            Console.Write("Введите порядковый номер студента: ");
            string input = Console.ReadLine()!;
            if (int.TryParse(input, out int value) && (value >= 1 && value <= _group.GetStudentCount()))
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
