using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace SessionResultsCS
{
    public class TXTReportExporter : ReportExporter
    {
        private const char TABLE_CROSS_SYMBOL = '+';
        private const char TABLE_HORIZONTAL_SYMBOL = '-';
        private const char TABLE_VERTICAL_SYMBOL = '|';

        private const string FIO_COLUMN_HEADER = "ФИО";
        private const string AVERAGE_COLUMN_HEADER = "Средний балл";
        private const int EXTRA_COLUMNS_COUNT = 2;

        private const int MIN_COLUMN_WIDTH = 1;
        private const int RESULT_COLUMN_WIDTH = 3;
        private const int CELL_PADDING = 1;


        public TXTReportExporter(string filePath, string? title = null, string? body = null, bool includeDate = false)
            : base(filePath, title, body, includeDate)
        {
        }


        public override void Export(GroupTable groupTable)
        {
            GroupTableData data = groupTable.GetTableData();
            int[] widths = CalculateColumnWidths(data);
            string separator = TableSeparator(widths);

            using (StreamWriter writer = new StreamWriter(FilePath))
            {
                if (Title != null)
                {
                    writer.WriteLine(Title);
                    writer.WriteLine();
                }
                if (Body != null)
                {
                    writer.WriteLine(Body);
                    writer.WriteLine();
                }
                if (IncludeDate)
                {
                    writer.WriteLine($"Дата генерации: {DateTime.Today.ToShortDateString()}");
                    writer.WriteLine();
                }

                writer.WriteLine(separator);
                writer.WriteLine(TableHeader(widths));
                writer.WriteLine(separator);
                foreach (string row in TableBodyToStrings(data, widths))
                {
                    writer.WriteLine(row);
                }
                writer.WriteLine(separator);
                writer.WriteLine(TableDisciplineAverages(data, widths));
                writer.WriteLine(separator);

                writer.WriteLine();

                for (int i = 0; i < data.Disciplines.Length; i++)
                {
                    writer.WriteLine($"{i + 1} - {data.Disciplines[i].Name}");
                }
            }
        }


        private static int[] CalculateColumnWidths(GroupTableData data)
        {
            int[] widths = new int[data.Disciplines.Length + EXTRA_COLUMNS_COUNT];
            for (int i = 0; i < widths.Length; i++)
            {
                widths[i] = MIN_COLUMN_WIDTH;
            }
            foreach (Student student in data.Students)
            {
                widths[0] = Math.Max(widths[0], student.GetLastNameWithInitials().Length);
            }
            for (int i = 1; i <= data.Disciplines.Length; i++)
            {
                widths[i] = Math.Max(widths[i], RESULT_COLUMN_WIDTH);
            }
            widths[widths.Length - 1] = Math.Max(widths[widths.Length - 1], AVERAGE_COLUMN_HEADER.Length);

            return widths;
        }

        private static string TableSeparator(int[] widths)
        {
            StringBuilder builder = new StringBuilder();
            builder.Append(TABLE_CROSS_SYMBOL);
            foreach (int width in widths)
            {
                builder.Append(TABLE_HORIZONTAL_SYMBOL, width + CELL_PADDING * 2);
                builder.Append(TABLE_CROSS_SYMBOL);
            }
            return builder.ToString();
        }

        private static string TableRow(string[] cells, int[] widths)
        {
            StringBuilder builder = new StringBuilder();
            builder.Append(TABLE_VERTICAL_SYMBOL);
            for (int i = 0; i < widths.Length; i++)
            {
                builder.Append(' ', CELL_PADDING);
                builder.Append(cells[i].PadLeft(widths[i]));
                builder.Append(' ', CELL_PADDING);
                builder.Append(TABLE_VERTICAL_SYMBOL);
            }
            return builder.ToString();
        }

        private static string TableHeader(int[] widths)
        {
            string[] cells = new string[widths.Length];
            cells[0] = FIO_COLUMN_HEADER;
            for (int i = 1; i <= widths.Length - 2; i++)
            {
                cells[i] = i.ToString();
            }
            cells[widths.Length - 1] = AVERAGE_COLUMN_HEADER;

            return TableRow(cells, widths);
        }

        private static string[] TableBodyToStrings(GroupTableData data, int[] widths)
        {
            string[] result = new string[data.Students.Length];

            int[] studentAverages = data.StudentAverages();
            for (int i = 0; i < data.Students.Length; i++)
            {
                string[] cells = new string[widths.Length];

                cells[0] = data.Students[i].GetLastNameWithInitials();
                for (int j = 0; j < data.Disciplines.Length; j++)
                {
                    cells[j + 1] = data.TableBody[i, j]?.ToStringCompact() ?? "";
                }
                cells[widths.Length - 1] = studentAverages[i].ToString();

                result[i] = TableRow(cells, widths);
            }

            return result;
        }

        private string TableDisciplineAverages(GroupTableData data, int[] widths)
        {
            string[] cells = new string[widths.Length];

            cells[0] = "";
            int[] disciplineAverages = data.DisciplineAverages();
            for (int i = 1; i <= data.Disciplines.Length; i++)
            {
                cells[i] = disciplineAverages[i - 1].ToString();
            }
            cells[widths.Length - 1] = data.GroupAverage().ToString();

            return TableRow(cells, widths);
        }
    }
}
