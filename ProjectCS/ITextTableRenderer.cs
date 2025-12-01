using System;

namespace SessionResultsCS
{
    // Объект, преобразующий таблицу в текст
    public interface ITextTableRenderer
    {
        // Преобразует таблицу в текст
        string RenderTable(GroupTableData data);
    }
}
