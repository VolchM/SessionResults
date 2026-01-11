using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace SessionResultsCS
{
    public class TXTReportExporter : FileReportExporter
    {
        public ITextTableRenderer Renderer { get; set; }


        public TXTReportExporter(string filePath, ITextTableRenderer renderer, string title = "", string body = "", bool includeDate = false)
            : base(filePath, title, body, includeDate)
        {
            Renderer = renderer;
        }


        public override void Export(GroupTable groupTable)
        {
            GroupTableData data = groupTable.GetTableData();
            
            using (StreamWriter writer = new StreamWriter(FilePath))
            {
                if (Title != "")
                {
                    writer.WriteLine(Title);
                    writer.WriteLine();
                }
                if (Body != "")
                {
                    writer.WriteLine(Body);
                    writer.WriteLine();
                }
                if (IncludeDate)
                {
                    writer.WriteLine($"Дата генерации: {DateTime.Today.ToShortDateString()}");
                    writer.WriteLine();
                }

                writer.WriteLine(Renderer.RenderTable(data));
                writer.WriteLine();

                for (int i = 0; i < data.Disciplines.Length; i++)
                {
                    writer.WriteLine($"{i + 1} - {data.Disciplines[i].Name}");
                }
            }
        }
    }
}
