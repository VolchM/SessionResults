using System;

namespace SessionResultsCS
{
    public interface IReportExporter
    {
        // Экспортирует таблицу группы
        void Export(GroupTable groupTable);
    }
}
