using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace SessionResultsCS
{
    public class Group
    {
        public const int STUDENT_NOT_FOUND = -1;

        private string _name;
        private int _course;
        // Cписок студентов
        private List<Student> _students;


        // Название группы
        public string Name
        {
            get { return _name; }
            set
            {
                string newName = value.Trim();
                if (newName.Length == 0)
                {
                    throw new ArgumentException("Group name cannot be empty");
                }
                _name = newName;
            }
        }

        // Курс обучения
        public int Course
        {
            get { return _course; }
            set
            {
                if (!(value >= Speciality.MIN_COURSE && value <= Speciality.MAX_COURSE))
                {
                    throw new ArgumentException("Invalid course value");
                }
                _course = value;
            }
        }

        // Специальность группы
        public Speciality Speciality { get; }


        public Group(Speciality speciality, string name, int course)
        {
            Speciality = speciality;
            Name = name;
            Course = course;
            _students = new List<Student>();
        }


        // Возвращает список дисциплин группы
        public DisciplineList GetDisciplineList()
        {
            return Speciality.GetDisciplineList(Course);
        }

        // Возвращает количество студентов в группе
        public int GetStudentCount()
        {
            return _students.Count;
        }

        // Возвращает студента по указанному индексу
        public Student GetStudentAt(int index)
        {
            return _students[index];
        }

        // Возврашает список студентов
        public ReadOnlyCollection<Student> GetStudents()
        {
            return _students.AsReadOnly();
        }

        // Находит студента по номеру студенческго билета и возвращает его индекс. Если такого студента нет в списке возвращает STUDENT_NOT_FOUND
        public int FindStudentByID(uint studentID)
        {
            return _students.FindIndex(student => student.StudentID == studentID);
        }

        // Добавляет студента и возвращает true при успешном добавлении, иначе false
        public void AddStudent(Student student)
        {
            if (FindStudentByID(student.StudentID) != STUDENT_NOT_FOUND)
            {
                throw new ArgumentException("Added student is already in group");
            }
            _students.Add(student);
        }

        // Удаляет студента по номеру студенческого билета
        public void DeleteStudentByID(uint studentID)
        {
            int index = FindStudentByID(studentID);
            if (index == STUDENT_NOT_FOUND)
            {
                throw new ArgumentException("Deleted student is not in group");
            }
            _students.RemoveAt(index);
        }

        // Удаляет студента
        public void DeleteStudent(Student student)
        {
            DeleteStudentByID(student.StudentID);
        }
    }
}
