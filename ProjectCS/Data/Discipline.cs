using System;

namespace SessionResultsCS
{
    // Перечисление типов аттестации
    public enum AttestationType
    {
        Exam,           // Экзамен
        PassFailExam    // Зачёт
    }

    public class Discipline
    {
        private string _name;


        // Название дисциплины
        public string Name {
            get { return _name; }
            set
            {
                string newName = value.Trim();
                if (newName.Length == 0)
                {
                    throw new ArgumentException("Discipline name cannot be empty");
                }
                _name = newName;
            }
        }

        // Тип аттестации
        public AttestationType AttestationType { get; set; }


        public Discipline(string name, AttestationType attestationType)
        {
            Name = name;
            AttestationType = attestationType;
        }


        public Discipline Clone()
        {
            return new Discipline(Name, AttestationType);
        }


        // Проверяет равенство с другой дисциплин
        public override bool Equals(object? obj)
        {
            if (obj is Discipline other)
            {
                return this == other;
            }
            return false;
        }


        public static bool operator ==(Discipline left, Discipline right)
        {
            return left.Name == right.Name && left.AttestationType == right.AttestationType;
        }

        public static bool operator !=(Discipline left, Discipline right)
        {
            return !(left == right);
        }
    }
}
