using System;
using System.Collections.Generic;
using System.Linq;

namespace SessionResultsCS.UI
{
    public class StudentPage : LoopPage
    {
        private Student _student;

        private MenuActionPicker _picker;


        public StudentPage(Student student)
        {
            _student = student;
            _picker = new MenuActionPicker([
                ("Изменить номер студенческого билета", ChangeStudentID),
                ("Изменить имя студента", ChangeStudentFirstName),
                ("Изменить фамилию студента", ChangeStudentLastName),
                ("Изменить отчество студента", ChangeStudentMiddleName),
                ("Назад", StopLoop),
            ]);
        }

        protected override void Loop()
        {
            Console.WriteLine($"== {_student} ==");
            Console.WriteLine("Действия:");
            _picker.PickAndRun();
        }


        private void ChangeStudentID()
        {
            try
            {
                Console.Write("Введите новый номер студенческого билета: ");
                string studentID = Console.ReadLine()!;
                _student.StudentID = uint.Parse(studentID);
            }
            catch (Exception e) when (e is ArgumentException || e is FormatException)
            {
                Console.WriteLine("Введен некорректный курс");
            }
        }

        private void ChangeStudentFirstName()
        {
            try
            {
                Console.Write("Введите новое имя студента: ");
                string firstName = Console.ReadLine()!;
                _student.FirstName = firstName;
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Введено некорректное имя");
            }
        }

        private void ChangeStudentLastName()
        {
            try
            {
                Console.Write("Введите новую фамилию студента: ");
                string lastName = Console.ReadLine()!;
                _student.LastName = lastName;
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Введена некорректная фамилия");
            }
        }

        private void ChangeStudentMiddleName()
        {
            try
            {
                Console.Write("Введите новое отчество студента: ");
                string middleName = Console.ReadLine()!;
                _student.MiddleName = middleName;
            }
            catch (ArgumentException)
            {
                Console.WriteLine("Введено некорректное отчество");
            }
        }
    }
}
