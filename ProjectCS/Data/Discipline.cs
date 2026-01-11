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
        // Название дисциплины
        public string Name { get; }

        // Тип аттестации
        public AttestationType AttestationType { get; }


        public Discipline(string name, AttestationType attestationType)
        {
            string trimmedName = name.Trim();
            if (trimmedName.Length == 0)
            {
                throw new ArgumentException("Discipline name cannot be empty");
            }
            Name = trimmedName;
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

        public override string ToString()
        {
            return $"{Name} - {AttestationType switch { AttestationType.Exam => "Экзамен", AttestationType.PassFailExam => "Зачёт" }}";
        }


        public static bool operator ==(Discipline left, Discipline right)
        {
            return left.Name == right.Name && left.AttestationType == right.AttestationType;
        }

        public static bool operator !=(Discipline left, Discipline right)
        {
            return !(left == right);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Name, AttestationType);
        }
    }
}
