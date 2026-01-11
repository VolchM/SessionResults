using System;

namespace SessionResultsCS
{
    public class Student
    {
        private string _firstName;
        private string _lastName;
        private string _middleName;


        // Номер студенческого билета
        public uint StudentID { get; set; }

        // Имя
        public string FirstName
        {
            get { return _firstName; }
            set
            {
                if (value.Contains(' ') || value.Length == 0)
                {
                    throw new ArgumentException("First name cannot contain spaces or be empty");
                }
                _firstName = value;
            }
        }

        // Фамилия
        public string LastName
        {
            get { return _lastName; }
            set
            {
                if (value.Contains(' ') || value.Length == 0)
                {
                    throw new ArgumentException("Last name cannot contain spaces or be empty");
                }
                _lastName = value;
            }
        }

        // Отчество
        public string MiddleName
        {
            get { return _middleName; }
            set
            {
                if (value.Contains(' ') || value.Length == 0)
                {
                    throw new ArgumentException("Middle name cannot contain spaces or be empty");
                }
                _middleName = value;
            }
        }

        // Группа
        public Group Group { get; }

        // Результаты сессии
        public SessionResults SessionResults { get; }


        public Student(Group group, uint studentID, string firstName, string lastName, string middleName)
        {
            Group = group;
            StudentID = studentID;
            FirstName = firstName;
            LastName = lastName;
            MiddleName = middleName;
            SessionResults = new SessionResults();
        }


        // Возвращает полное имя (фамилию, имя и отчество)
        public string GetFullName()
        {
            return $"{FirstName} {LastName} {MiddleName}";
        }

        // Возвращает фамилию и инициалы
        public string GetLastNameWithInitials()
        {
            return $"{LastName} {FirstName[0]}. {MiddleName[0]}.";
        }
    }
}
