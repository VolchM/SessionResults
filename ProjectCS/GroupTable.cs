using System;
using System.Linq;

namespace SessionResultsCS
{
    // Перечисление порядков сортировки
    public enum SortOrder {
        Ascending,  // По возрастанию
        Descending  // По убыванию
    }

    public class GroupTable
    {
        // Выбранный порядок сортировки
        private SortOrder _sortOrder;
        // Выбранная дисциплина для сортировки, либо средний балл
        private Discipline? _sortColumn;


        // Группа
        public Group Group { get; }

        // Включить только неуспевающих студентов
        public bool IncludeOnlyFailing { get; set; }

        // Cписок дисциплин, по которым составляется таблица
        public DisciplineList Disciplines { get; set; }


        public GroupTable(Group group, bool includeOnlyFailing = false)
        {
            Group = group;
            IncludeOnlyFailing = includeOnlyFailing;
            Disciplines = new DisciplineList();
            _sortColumn = null;
            _sortOrder = SortOrder.Ascending;
        }


        // Сортирует студентов по результатам дисциплины
        public void SortByDiscipline(Discipline discipline, SortOrder sortOrder)
        {
            _sortColumn = discipline;
            _sortOrder = sortOrder;
        }

        // Сортирует студентов по среднему баллу
        public void SortByAverage(SortOrder sortOrder)
        {
            _sortColumn = null;
            _sortOrder = sortOrder;
        }


        // Создает и возвращает данные таблицы
        public GroupTableData GetTableData()
        {
            Student[] students;
            Discipline[] disciplines;
            AttestationResult?[,] tableBody;

            disciplines = Disciplines.ToArray();


            if (IncludeOnlyFailing)
            {
                students = Group.GetStudents().Where(st => 
                    disciplines.Select(d => st.SessionResults.GetResult(d))
                               .Any(res => res is null || !res.IsPassed())
                ).ToArray();
            }
            else
            {
                students = Group.GetStudents().ToArray();
            }

            Func<Student, int> func;
            if (_sortColumn is not null)
            {
                func = student => student.SessionResults.GetResult(_sortColumn)?.ToScore() ?? 0;
            }
            else
            {
                func = student =>
                {
                    int sum = 0;
                    foreach (Discipline discipline in disciplines)
                    {
                        if (discipline.AttestationType == AttestationType.Exam)
                        {
                            sum += student.SessionResults.GetResult(discipline)?.ToScore() ?? 0;
                        }
                    }
                    return sum;
                };
            }
            students = (_sortOrder == SortOrder.Ascending
                ? students.OrderBy(func)
                : students.OrderByDescending(func)
            ).ToArray();


            tableBody = new AttestationResult?[students.Length, disciplines.Length];
            for (int i = 0; i < students.Length; i++)
            {
                for (int j = 0; j < disciplines.Length; j++)
                {
                    tableBody[i, j] = students[i].SessionResults.GetResult(disciplines[j]);
                }
            }

            return new GroupTableData(students, disciplines, tableBody);
        }
    }
}
