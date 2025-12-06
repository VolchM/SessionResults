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
            AttestationResult?[][] tableBody;

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
                func = student => disciplines
                    .Where(discipline => discipline.AttestationType == AttestationType.Exam)
                    .Select(discipline => student.SessionResults.GetResult(discipline)?.ToScore() ?? 0)
                    .Sum();
            }
            students = (_sortOrder == SortOrder.Ascending
                ? students.OrderBy(func)
                : students.OrderByDescending(func)
            ).ToArray();

            tableBody = students
                .Select(student => disciplines
                    .Select(discipline => student.SessionResults.GetResult(discipline))
                    .ToArray()
                ).ToArray();

            return new GroupTableData(students, disciplines, tableBody);
        }
    }
}
