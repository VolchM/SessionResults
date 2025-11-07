using System;

namespace SessionResultsCS
{
    class Program
    {
        static void Main()
        {
            Console.WriteLine("------- Демонстрация работы программы -------");

            Speciality pi = new Speciality("09.03.04", "Программная инженерия");
            pi.GetDisciplineList(2).AddDiscipline(new Discipline("Иностранный язык", AttestationType.PassFailExam));
            pi.GetDisciplineList(2).AddDiscipline(new Discipline("Программирование", AttestationType.Exam));
            pi.GetDisciplineList(2).AddDiscipline(new Discipline("Архитектура ЭВМ", AttestationType.Exam));


            Group pi43 = new Group(pi, "ПИ-43", 2);
            pi.AddGroup(pi43);

            pi43.AddStudent(new Student(pi43, 12300325, "Иван", "Иванов", "Иванович"));
            pi43.AddStudent(new Student(pi43, 12300326, "Пётр", "Петров", "Петрович"));
            pi43.AddStudent(new Student(pi43, 12307377, "Сергей", "Сергеев", "Сергеевич"));
            pi43.AddStudent(new Student(pi43, 12303537, "Алексей", "Алексеев", "Алексеевич"));
            pi43.AddStudent(new Student(pi43, 12303890, "Дмитрий", "Дмитриев", "Дмитриевич"));


            Random rand = new Random(1);
            foreach (Student student in pi43.GetStudents())
            {
                foreach (Discipline discipline in pi.GetDisciplineList(2).GetDisciplines())
                {
                    if (discipline.AttestationType == AttestationType.Exam)
                    {
                        student.SessionResults.SetResult(discipline, new ExamResult(rand.Next(0, 101)));
                    }
                    else
                    {
                        student.SessionResults.SetResult(discipline, new PassFailExamResult(rand.Next(0,2) == 1));
                    }
                }
            }


            Console.WriteLine($"{pi.Code} {pi.Name} {pi.GetGroupAt(0).Name}");

            for (int i = 0; i < pi43.GetStudentCount(); i++)
            {
                Console.WriteLine($"{i+1}. {pi43.GetStudentAt(i).GetFullName()}");
            }


            GroupTable groupTable = new GroupTable(pi43);
            groupTable.Disciplines = new DisciplineList(pi.GetDisciplineList(2).GetDisciplines());
            groupTable.SortByDiscipline(groupTable.Disciplines.GetDisciplineAt(1), SortOrder.Ascending);

            GroupTableData data = groupTable.GetTableData();

            Console.WriteLine();
            for (int i = 0; i < data.Students.Length; i++)
            {
                Console.Write("{0}: ", data.Students[i].GetLastNameWithInitials());
                for (int j = 0; j < data.Disciplines.Length; j++)
                {
                    Console.Write("{0} ", data.TableBody[i, j]?.ToString() ?? "_");
                }
                Console.WriteLine();
            }
            Console.WriteLine($"Средний балл группы: {data.GroupAverage()}");
            Console.WriteLine();

            ReportExporter exporter = new TXTReportExporter("report1.txt", "Отчёт об успеваемости студентов группы ПИ-43");
            exporter.Export(groupTable);
            Console.WriteLine("Отчёт сохранён в report1.txt");


            groupTable.Disciplines.RemoveDisciplineAt(1);
            groupTable.SortByAverage(SortOrder.Descending);
            groupTable.IncludeOnlyFailing = true;

            exporter.FilePath = "report2.txt";
            exporter.Title = "Отчёт о неуспевающих студентах группы ПИ-43";
            exporter.IncludeDate = true;
            exporter.Export(groupTable);
            Console.WriteLine("Отчёт сохранён в report2.txt");

            Console.Write("Нажмите Enter, чтобы закрыть программу...");
            Console.ReadLine();
        }
    }
}
