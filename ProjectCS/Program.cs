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
                foreach (Discipline discipline in pi43.GetDisciplineList())
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


            ResultsList<ExamResult> resultsList1 = new ResultsList<ExamResult>(pi43.GetStudents(), pi43.GetDisciplineList().GetDisciplineAt(1));
            resultsList1.AddRange([new ExamResult(100), new ExamResult(90)]);
            Console.WriteLine($"Results: {string.Join(", ", resultsList1)}");
            Console.WriteLine($"Average score: {resultsList1.AverageScore()}, pass percent: {resultsList1.PassedPercent():0.##}");

            ResultsList<PassFailExamResult> resultsList2 = new ResultsList<PassFailExamResult>(pi43.GetStudents(), pi43.GetDisciplineList().GetDisciplineAt(0));
            resultsList2.AddRange([new PassFailExamResult(true), new PassFailExamResult(false)]);
            Console.WriteLine($"Results: {string.Join(", ", resultsList2)}");
            Console.WriteLine($"Average score: {resultsList2.AverageScore()}, pass percent: {resultsList2.PassedPercent():0.##}");


            GroupTable groupTable = new GroupTable(pi43);
            groupTable.Disciplines = pi43.GetDisciplineList().ShallowClone();
            groupTable.SortByDiscipline(groupTable.Disciplines.GetDisciplineAt(1), SortOrder.Ascending);


            IReportExporter exporter1 = new TXTReportExporter("report1.txt", StyledTextTableRenderer.Default, "Отчёт об успеваемости студентов группы ПИ-43");
            exporter1.Export(groupTable);
            Console.WriteLine("Отчёт сохранён в report1.txt");

            groupTable.Disciplines.RemoveDisciplineAt(1);
            groupTable.SortByAverage(SortOrder.Descending);
            groupTable.IncludeOnlyFailing = true;

            IReportExporter exporter2 = new TXTReportExporter("report2.txt", new StyledTextTableRenderer('0', '=', '|'), "Отчёт о неуспевающих студентах группы ПИ-43", includeDate: true);
            exporter2.Export(groupTable);
            Console.WriteLine("Отчёт сохранён в report2.txt");

            groupTable.Disciplines.RemoveDisciplineAt(1);
            groupTable.Disciplines.AddDiscipline(pi43.GetDisciplineList().GetDisciplineAt(1));

            IReportExporter exporter3 = new TXTReportExporter("report3.txt", new OutlinedTextTableRenderer('0', '-', '|'), "Отчёт о неуспевающих студентах группы ПИ-43", includeDate: true);
            exporter3.Export(groupTable);
            Console.WriteLine("Отчёт сохранён в report3.txt");

            Console.Write("Нажмите Enter, чтобы закрыть программу...");
            Console.ReadLine();
        }
    }
}
