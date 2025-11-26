using System;
using System.Collections.Generic;
using System.Linq;

namespace SessionResultsCS
{
    public class GroupTableData
    {
        public const string FIO_COLUMN_HEADER = "ФИО";
        public const string AVERAGE_COLUMN_HEADER = "Средний балл";
        public const int EXTRA_COLUMNS_COUNT = 2;


        // Массив студентов в порядке вхождения в таблицу
        public Student[] Students { get; }

        // Массив дисциплин в порядке вхождения в таблицу
        public Discipline[] Disciplines { get; }

        // Двумерный массив результатов аттестации
        public AttestationResult?[,] TableBody { get; }


        public GroupTableData(Student[] students, Discipline[] disciplines,
            AttestationResult?[,] tableBody)
        {
            if (tableBody.GetLength(0) != students.Length || tableBody.GetLength(1) != disciplines.Length)
            {
                throw new ArgumentException("Invalid tableData size");
            }
            Students = students;
            Disciplines = disciplines;
            TableBody = tableBody;
            
        }


        // Возвращает массив средних баллов студентов по экзаменам
        public int[] StudentAverages()
        {
            int[] studentAverages = new int[Students.Length];
            for (int i = 0; i < Students.Length; i++)
            {
                int k = 0;
                for (int j = 0; j < Disciplines.Length; j++)
                {
                    if (Disciplines[j].AttestationType == AttestationType.Exam)
                    {
                        studentAverages[i] += TableBody[i, j]?.ToScore() ?? 0;
                        k += 1;
                    }
                }
                if (k != 0)
                {
                    studentAverages[i] /= k;
                }
            }

            return studentAverages;
        }

        // Возвращает массив средних баллов/процентов сдачи по дисциплинам
        public int[] DisciplineAverages()
        {
            int[] disciplineAverages = new int[Disciplines.Length];
            for (int j = 0; j < Disciplines.Length; j++)
            {
                for (int i = 0; i < Students.Length; i++)
                {
                    disciplineAverages[j] += TableBody[i, j]?.ToScore() ?? 0;
                }
                if (Students.Length != 0)
                {
                    disciplineAverages[j] /= Students.Length;
                }
            }

            return disciplineAverages;
        }


        public int GroupAverage()
        {
            return (int)StudentAverages().Average();
        }


        public string[] TableHeader()
        {
            string[] cells = new string[Disciplines.Length + EXTRA_COLUMNS_COUNT];
            cells[0] = FIO_COLUMN_HEADER;
            for (int i = 1; i <= Disciplines.Length; i++)
            {
                cells[i] = i.ToString();
            }
            cells[cells.Length - 1] = AVERAGE_COLUMN_HEADER;

            return cells;
        }

        public string[][] TableBodyToStrings(bool compactResults)
        {
            string[][] result = new string[Students.Length][];

            int[] studentAverages = StudentAverages();
            for (int i = 0; i < Students.Length; i++)
            {
                string[] cells = new string[Disciplines.Length + EXTRA_COLUMNS_COUNT];

                cells[0] = Students[i].GetLastNameWithInitials();
                for (int j = 0; j < Disciplines.Length; j++)
                {
                    if (compactResults)
                    {
                        cells[j + 1] = TableBody[i, j]?.ToStringCompact() ?? "";
                    }
                    else
                    {
                        cells[j + 1] = TableBody[i, j]?.ToString() ?? "";
                    }
                }
                cells[cells.Length - 1] = studentAverages[i].ToString();

                result[i] = cells;
            }

            return result;
        }

        public string[] TableDisciplineAverages()
        {
            string[] cells = new string[Disciplines.Length + EXTRA_COLUMNS_COUNT];

            cells[0] = "";
            int[] disciplineAverages = DisciplineAverages();
            for (int i = 1; i <= Disciplines.Length; i++)
            {
                cells[i] = disciplineAverages[i - 1].ToString();
            }
            cells[cells.Length - 1] = GroupAverage().ToString();

            return cells;
        }
    }
}
