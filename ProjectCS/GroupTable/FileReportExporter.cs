using System;
using System.Collections.Generic;

namespace SessionResultsCS
{
    public abstract class FileReportExporter : IReportExporter
    {
        // Путь к файлу для сохранения отчёта
        public string FilePath { get; set; }
        // Заголовок отчета
        public string Title { get; set; }
        // Текст отчета
        public string Body { get; set; }
        // Включать ли дату генерации в отчет
        public bool IncludeDate { get; set; }


        public FileReportExporter(string filePath, string title = "", string body = "", bool includeDate = false)
        {
            FilePath = filePath;
            Title = title;
            Body = body;
            IncludeDate = includeDate;
        }


        // Экспортирует таблицу группы
        public abstract void Export(GroupTable groupTable);
    }
}
