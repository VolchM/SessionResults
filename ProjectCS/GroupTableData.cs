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
        public AttestationResult?[][] TableBody { get; }


        public GroupTableData(Student[] students, Discipline[] disciplines,
            AttestationResult?[][] tableBody)
        {
            if (tableBody.Length != students.Length || tableBody.Any(row => row.Length != disciplines.Length))
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
            return TableBody
                .Select(row => (int)row
                    .Where((result, j) => Disciplines[j].AttestationType == AttestationType.Exam)
                    .Select(result => result?.ToScore() ?? 0)
                    .DefaultIfEmpty(0)
                    .Average()
                ).ToArray();
        }

        // Возвращает массив средних баллов/процентов сдачи по дисциплинам
        public int[] DisciplineAverages()
        {
            return Disciplines
                .Select((discipline, j) => (int)Students
                    .Select((student, i) => TableBody[i][j]?.ToScore() ?? 0)
                    .DefaultIfEmpty(0)
                    .Average()
                ).ToArray();
        }


        public int GroupAverage()
        {
            return (int)StudentAverages().Average();
        }


        public string[] TableHeader()
        {
            return [FIO_COLUMN_HEADER, .. Enumerable.Range(1, Disciplines.Length).Select(i => i.ToString()), AVERAGE_COLUMN_HEADER];
        }

        public string[][] TableBodyToStrings(bool compactResults)
        {
            int[] studentAverages = StudentAverages();

            return Students
                .Select<Student, string[]>((student, i) =>
                    [student.GetLastNameWithInitials(),
                    .. TableBody[i].Select(result => (compactResults ? result?.ToStringCompact() : result?.ToString()) ?? ""),
                    studentAverages[i].ToString()]
                ).ToArray();
        }

        public string[] TableDisciplineAverages()
        {
            return ["", .. DisciplineAverages().Select(avg => avg.ToString()), GroupAverage().ToString()];
        }
    }
}
