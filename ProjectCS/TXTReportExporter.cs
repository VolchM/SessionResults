using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace SessionResultsCS
{
    public class TXTReportExporter : FileReportExporter
    {
        public const char TABLE_CROSS_SYMBOL = '+';
        public const char TABLE_HORIZONTAL_SYMBOL = '-';
        public const char TABLE_VERTICAL_SYMBOL = '|';

        public const int MIN_COLUMN_WIDTH = 1;
        public const int RESULT_COLUMN_WIDTH = 3;
        public const int CELL_PADDING = 1;


        public TXTReportExporter(string filePath, string? title = null, string? body = null, bool includeDate = false)
            : base(filePath, title, body, includeDate)
        {
        }


        public override void Export(GroupTable groupTable)
        {
            GroupTableData data = groupTable.GetTableData();
            

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

                writer.WriteLine(RenderTable(data));
                writer.WriteLine();

                for (int i = 0; i < data.Disciplines.Length; i++)
                {
                    writer.WriteLine($"{i + 1} - {data.Disciplines[i].Name}");
                }
            }
        }


        // Преобразует таблицу в текст
        public virtual string RenderTable(GroupTableData data)
        {
            int[] widths = CalculateColumnWidths(data);
            string separator = TableSeparator(widths, TABLE_CROSS_SYMBOL, TABLE_HORIZONTAL_SYMBOL);

            StringBuilder builder = new StringBuilder();

            builder.AppendLine(separator);
            builder.AppendLine(TableRow(data.TableHeader(), widths, TABLE_VERTICAL_SYMBOL));
            builder.AppendLine(separator);
            foreach (string[] cells in data.TableBodyToStrings(true))
            {
                builder.AppendLine(TableRow(cells, widths, TABLE_VERTICAL_SYMBOL));
            }
            builder.AppendLine(separator);
            builder.AppendLine(TableRow(data.TableDisciplineAverages(), widths, TABLE_VERTICAL_SYMBOL));
            builder.Append(separator);

            return builder.ToString();
        }


        protected static int[] CalculateColumnWidths(GroupTableData data)
        {
            int[] widths = new int[data.Disciplines.Length + GroupTableData.EXTRA_COLUMNS_COUNT];
            for (int i = 0; i < widths.Length; i++)
            {
                widths[i] = MIN_COLUMN_WIDTH;
            }
            widths[0] = Math.Max(widths[0], GroupTableData.FIO_COLUMN_HEADER.Length);
            foreach (Student student in data.Students)
            {
                widths[0] = Math.Max(widths[0], student.GetLastNameWithInitials().Length);
            }
            for (int i = 1; i <= data.Disciplines.Length; i++)
            {
                widths[i] = Math.Max(widths[i], RESULT_COLUMN_WIDTH);
            }
            widths[widths.Length - 1] = Math.Max(widths[widths.Length - 1], GroupTableData.AVERAGE_COLUMN_HEADER.Length);

            return widths;
        }

        protected static string TableSeparator(int[] widths, char crossSymbol, char horizontalSymbol)
        {
            StringBuilder builder = new StringBuilder();
            builder.Append(crossSymbol);
            foreach (int width in widths)
            {
                builder.Append(horizontalSymbol, width + CELL_PADDING * 2);
                builder.Append(crossSymbol);
            }
            return builder.ToString();
        }

        protected static string TableRow(string[] cells, int[] widths, char verticalSymbol)
        {
            StringBuilder builder = new StringBuilder();
            builder.Append(verticalSymbol);
            for (int i = 0; i < widths.Length; i++)
            {
                builder.Append(' ', CELL_PADDING);
                builder.Append(cells[i].PadLeft(widths[i]));
                builder.Append(' ', CELL_PADDING);
                builder.Append(verticalSymbol);
            }
            return builder.ToString();
        }
    }
}
