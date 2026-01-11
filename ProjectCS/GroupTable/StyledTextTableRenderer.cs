using System;
using System.Text;

namespace SessionResultsCS
{
    public class StyledTextTableRenderer : ITextTableRenderer
    {
        public const int MIN_COLUMN_WIDTH = 1;
        public const int RESULT_COLUMN_WIDTH = 3;
        public const int CELL_PADDING = 1;

        public static StyledTextTableRenderer Default { get; } = new StyledTextTableRenderer('+', '-', '|');


        // Символы, используемые для создания таблицы
        public char CrossSymbol { get; }
        public char HorizontalSymbol { get; }
        public char VerticalSymbol { get; }


        public StyledTextTableRenderer(char crossSymbol, char horizontalSymbol, char verticalSymbol)
        {
            CrossSymbol = crossSymbol;
            HorizontalSymbol = horizontalSymbol;
            VerticalSymbol = verticalSymbol;
        }


        public virtual string RenderTable(GroupTableData data)
        {
            int[] widths = CalculateColumnWidths(data);
            string separator = TableSeparator(widths, CrossSymbol, HorizontalSymbol);

            StringBuilder builder = new StringBuilder();

            builder.AppendLine(separator);
            builder.AppendLine(TableRow(data.TableHeader(), widths, VerticalSymbol));
            builder.AppendLine(separator);
            foreach (string[] cells in data.TableBodyToStrings(true))
            {
                builder.AppendLine(TableRow(cells, widths, VerticalSymbol));
            }
            builder.AppendLine(separator);
            builder.AppendLine(TableRow(data.TableDisciplineAverages(), widths, VerticalSymbol));
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
