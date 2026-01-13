using System;
using System.Collections.Generic;
using System.Linq;


namespace SessionResultsCS.UI
{
    public class GroupTablePage : IPage
    {
        private Faculty _faculty;

        public GroupTablePage(Faculty faculty)
        {
            _faculty = faculty;
        }

        public void Start()
        {
            if (_faculty.GetSpecialities().All(speciality => speciality.GetGroupCount() == 0))
            {
                Console.WriteLine("В факультете отсутствуют группы");
                return;
            }

            GroupTable groupTable = CreateGroupTable();

            PrintTable(groupTable);

            Console.WriteLine("Действия: ");
            new MenuActionPicker([
                ("Экспорт отчёта в TXT файл", () => { ExportToTXT(groupTable); }),
                ("Назад в главное меню", () => {}),
            ]).PickAndRun();
        }


        private GroupTable CreateGroupTable()
        {
            Console.WriteLine("Выберите специальность: ");
            ItemPicker specialityPicker = new ItemPicker(_faculty.GetSpecialities().Select(x => x.ToString()));
            Speciality speciality = _faculty.GetSpecialityAt(specialityPicker.Pick());


            Console.WriteLine("Выберите группу: ");
            ItemPicker groupPicker = new ItemPicker(speciality.GetGroups().Select(x => x.ToString()));
            Group group = speciality.GetGroupAt(groupPicker.Pick());


            Console.WriteLine("Выберите дисциплины: ");
            foreach (var (index, discipline) in group.GetDisciplineList().Index())
            {
                Console.WriteLine($"{index + 1}. {discipline}");
            }
            SortedSet<int> indices = new SortedSet<int>();
            bool readIndices = false;
            while (!readIndices)
            {
                indices.Clear();
                readIndices = true;

                Console.Write("Введите номера дисциплин через запятую (например: 1,3,4): ");
                string input = Console.ReadLine()!;
                foreach (string el in input.Split(","))
                {
                    if (int.TryParse(el, out int value)
                        && (value >= 1 && value <= group.GetDisciplineList().GetSize())
                        && !indices.Contains(value - 1))
                    {
                        indices.Add(value - 1);
                    }
                    else
                    {
                        readIndices = false;
                        Console.WriteLine("Номера введены неверно");
                        break;
                    }
                }
            }
            DisciplineList disciplines = new DisciplineList(indices.Select(index => group.GetDisciplineList().GetDisciplineAt(index)));


            ItemPicker sortPicker = new ItemPicker(["Средний балл", .. disciplines.Select(x => x.ToString())]);
            Console.WriteLine("Выберите столбец для сортировки: ");
            int sortSelection = sortPicker.Pick();

            QuickItemPicker sortOrderPicker = new QuickItemPicker(["По возрастанию", "По убыванию"]);
            Console.WriteLine("Выберите порядок сортировки: ");
            SortOrder sortOrder = sortOrderPicker.Pick() switch
            {
                0 => SortOrder.Ascending,
                1 => SortOrder.Descending
            };

            QuickItemPicker includeOnlyFailingPicker = new QuickItemPicker(["Включить всех студентов", "Включить только неуспевающих"]);
            Console.WriteLine("Выберите, включать ли всех студентов: ");
            bool includeOnlyFailing = includeOnlyFailingPicker.Pick() == 1;


            GroupTable groupTable = new GroupTable(group, includeOnlyFailing);
            groupTable.Disciplines = disciplines;

            if (sortSelection == 0)
            {
                groupTable.SortByAverage(sortOrder);
            }
            else
            {
                groupTable.SortByDiscipline(disciplines.GetDisciplineAt(sortSelection - 1), sortOrder);
            }

            return groupTable;
        }

        private void PrintTable(GroupTable groupTable)
        {
            GroupTableData data = groupTable.GetTableData();
            Console.WriteLine(StyledTextTableRenderer.Default.RenderTable(data));
            Console.WriteLine();

            for (int i = 0; i < data.Disciplines.Length; i++)
            {
                Console.WriteLine($"{i + 1} - {data.Disciplines[i].Name}");
            }
        }

        private void ExportToTXT(GroupTable groupTable)
        {
            var (fileName, title, body, includeDate) = GetReportExportData(".txt");

            QuickItemPicker tableStylePicker = new QuickItemPicker(["Обычный", "С двойным контуром"]);
            Console.WriteLine("Выберите стиль таблицы: ");
            int selectedTableStyle = tableStylePicker.Pick();

            Console.Write("Введите симбол таблицы на пересечении (по умолчанию: +): ");
            char crossSymbol = Console.ReadKey().KeyChar;
            if (crossSymbol == '\r') crossSymbol = '+';
            Console.WriteLine();

            Console.Write("Введите горизонтальный симбол таблицы (по умолчанию: -): ");
            char horizontalSymbol = Console.ReadKey().KeyChar;
            if (horizontalSymbol == '\r') horizontalSymbol = '-';
            Console.WriteLine();

            Console.Write("Введите вертикальный симбол таблицы (по умолчанию: |): ");
            char verticalSymbol = Console.ReadKey().KeyChar;
            if (verticalSymbol == '\r') verticalSymbol = '|';
            Console.WriteLine();

            ITextTableRenderer renderer;
            if (selectedTableStyle == 0)
            {
                renderer = new StyledTextTableRenderer(crossSymbol, horizontalSymbol, verticalSymbol);
            }
            else
            {
                renderer = new OutlinedTextTableRenderer(crossSymbol, horizontalSymbol, verticalSymbol);
            }

            IReportExporter exporter = new TXTReportExporter(fileName, renderer, title, body, includeDate);
            exporter.Export(groupTable);
            Console.WriteLine($"Отчёт сохранён в {fileName}");
        }

        private (string FileName, string Title, string Body, bool IncludeDate) GetReportExportData(string fileExtenstion)
        {
            Console.Write("Введите имя файла для сохранения отчёта: ");
            string fileName = Console.ReadLine()!;
            if (!fileName.EndsWith(fileExtenstion))
            {
                fileName += fileExtenstion;
            }

            Console.Write("Введите заголовок отчёта или пустую строку: ");
            string title = Console.ReadLine()!;

            Console.Write("Введите текст отчёта или пустую строку: ");
            string body = Console.ReadLine()!;

            QuickItemPicker includeDatePicker = new QuickItemPicker(["Не включать дату в отчёт", "Включать дату в отчёт"]);
            Console.WriteLine("Выберите, включать ли текущую дату в отчёт: ");
            bool includeDate = includeDatePicker.Pick() == 1;

            return (fileName, title, body, includeDate);
        }
    }
}
