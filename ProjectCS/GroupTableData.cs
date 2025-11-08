using System;
using System.Collections.Generic;
using System.Linq;

namespace SessionResultsCS
{
    public class GroupTableData
    {
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
    }
}
