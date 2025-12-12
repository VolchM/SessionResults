using System;
using System.IO;
using System.Text;

namespace SessionResultsCS
{
    public class OutlinedTextTableRenderer : StyledTextTableRenderer
    {
        public new static OutlinedTextTableRenderer Default { get; } = new OutlinedTextTableRenderer('+', '-', '|');


        public OutlinedTextTableRenderer(char crossSymbol, char horizontalSymbol, char verticalSymbol) :
            base(crossSymbol, horizontalSymbol, verticalSymbol) { }

        public override string RenderTable(GroupTableData data)
        {
            string table = base.RenderTable(data);
            int width = table.IndexOf(Environment.NewLine);
            string outline = CrossSymbol + new string(HorizontalSymbol, width) + CrossSymbol;

            StringBuilder builder = new StringBuilder();

            builder.AppendLine(outline);
            using (StringReader reader = new StringReader(table))
            {
                string? line;
                while ((line = reader.ReadLine()) != null) {
                    builder.Append(VerticalSymbol);
                    builder.Append(line);
                    builder.Append(VerticalSymbol);
                    builder.AppendLine();
                }
            }
            builder.Append(outline);

            return builder.ToString();
        }
    }
}
