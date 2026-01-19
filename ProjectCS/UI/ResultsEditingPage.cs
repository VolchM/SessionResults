using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SessionResultsCS.UI
{
    public class ResultsEditingPage : LoopPage
    {
        private Group _group;
        private Discipline _discipline;

        public ResultsEditingPage(Group group, Discipline discipline)
        {
            _group = group;
            _discipline = discipline;
            SetPicker(new MenuActionPicker([
                ("Изменить результат", ChangeResult),
                ("Удалить результат", DeleteResult),
                ("Сохранить изменения и вернуться в главное меню", StopLoop),
            ]));
        }

        protected override void Loop()
        {
            Console.WriteLine($"======== {_group}, {_discipline} ========");
            PrintResults();
        }


        private void ChangeResult()
        {
            int selectedIndex = SelectStudent();
            if (selectedIndex != -1)
            {
                AttestationResult newResult = ReadResult();
                _group.GetStudentAt(selectedIndex).SessionResults.SetResult(_discipline, newResult);
            }
        }

        private void DeleteResult()
        {
            int selectedIndex = SelectStudent();
            if (selectedIndex != -1)
            {
                _group.GetStudentAt(selectedIndex).SessionResults.DeleteResult(_discipline);
            }
        }


        private void PrintResults()
        {
            foreach (var (index, student) in _group.GetStudents().Index())
            {
                Console.WriteLine($"{index + 1}. {student}  -  {student.SessionResults.GetResult(_discipline)?.ToString() ?? "Нет результата"}");
            }
        }

        private int SelectStudent()
        {
            Console.Write("Введите порядковый номер студента: ");
            string input = Console.ReadLine()!;
            if (int.TryParse(input, out int value) && (value >= 1 && value <= _group.GetStudentCount()))
            {
                return value - 1;
            }
            else
            {
                Console.WriteLine("Введён неверный номер");
                return -1;
            }
        }

        private AttestationResult ReadResult()
        {
            return _discipline.AttestationType switch
            {
                AttestationType.PassFailExam => ReadPassFailExamResult(),
                AttestationType.Exam => ReadExamResult()
            };
        }

        private PassFailExamResult ReadPassFailExamResult()
        {
            QuickItemPicker resultPicker = new QuickItemPicker(["Незачёт", "Зачёт"]);
            Console.WriteLine("Выберите результат: ");
            return new PassFailExamResult(resultPicker.Pick() == 1);
        }

        private ExamResult ReadExamResult()
        {
            while (true)
            {
                try
                {
                    Console.Write($"Введите новый результат (от {ExamResult.MIN_SCORE} до {ExamResult.MAX_SCORE}): ");
                    string input = Console.ReadLine()!;
                    return new ExamResult(int.Parse(input));
                }
                catch (Exception e) when (e is ArgumentException || e is FormatException)
                {
                    Console.WriteLine("Введён некоректный результат");
                }
            }
        }
    }
}
