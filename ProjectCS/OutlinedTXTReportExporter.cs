using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SessionResultsCS
{
    public class OutlinedTXTReportExporter : TXTReportExporter
    {
        public OutlinedTXTReportExporter(string filePath, string? title = null, string? body = null, bool includeDate = false)
            : base(filePath, title, body, includeDate)
        {
        }

        public override string RenderTable(GroupTableData data)
        {
            string table = base.RenderTable(data);
            int width = table.IndexOf(Environment.NewLine);
            string outline = TABLE_CROSS_SYMBOL + new string(TABLE_HORIZONTAL_SYMBOL, width) + TABLE_CROSS_SYMBOL;

            StringBuilder builder = new StringBuilder();

            builder.AppendLine(outline);
            using (StringReader reader = new StringReader(table))
            {
                string? line;
                while ((line = reader.ReadLine()) != null) {
                    builder.Append(TABLE_VERTICAL_SYMBOL);
                    builder.Append(line);
                    builder.Append(TABLE_VERTICAL_SYMBOL);
                    builder.AppendLine();
                }
            }
            builder.Append(outline);

            return builder.ToString();
        }
    }
}
