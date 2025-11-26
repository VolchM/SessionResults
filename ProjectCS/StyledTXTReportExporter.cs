using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SessionResultsCS
{
    public class StyledTXTReportExporter : TXTReportExporter
    {
        // Стиль таблицы
        public class TableStyle
        {
            public char CrossSymbol { get; set; }
            public char HorizontalSymbol { get; set; }
            public char VerticalSymbol { get; set; }

            public TableStyle(char crossSymbol, char horizontalSymbol, char verticalSymbol)
            {
                CrossSymbol = crossSymbol;
                HorizontalSymbol = horizontalSymbol;
                VerticalSymbol = verticalSymbol;
            }
        }


        public TableStyle Style { get; set; }


        public StyledTXTReportExporter(string filePath, TableStyle style, string? title = null, string? body = null, bool includeDate = false)
            : base(filePath, title, body, includeDate)
        {
            Style = style;
        }

        public override string RenderTable(GroupTableData data)
        {
            int[] widths = CalculateColumnWidths(data);
            string separator = TableSeparator(widths, Style.CrossSymbol, Style.HorizontalSymbol);

            StringBuilder builder = new StringBuilder();

            builder.AppendLine(separator);
            builder.AppendLine(TableRow(data.TableHeader(), widths, Style.VerticalSymbol));
            builder.AppendLine(separator);
            foreach (string[] cells in data.TableBodyToStrings(true))
            {
                builder.AppendLine(TableRow(cells, widths, Style.VerticalSymbol));
            }
            builder.AppendLine(separator);
            builder.AppendLine(TableRow(data.TableDisciplineAverages(), widths, Style.VerticalSymbol));
            builder.Append(separator);

            return builder.ToString();
        }
    }
}
