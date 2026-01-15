#pragma once

#include "GroupTable/IReportExporter.hpp"
#include "GroupTable/GroupTable.hpp"

#include <string>


// Абстрактный класс для экспорта отчёта в файл
class FileReportExporter : public IReportExporter {
protected:
	std::string m_filePath; // Путь к файлу для сохранения отчёта
	std::string m_title; // Заголовок отчета
	std::string m_body; // Текст отчета
	bool m_includeDate; // Включать ли дату генерации в отчет

public:
	FileReportExporter(const std::string& filePath, const std::string& title = "", const std::string& body = "", bool includeDate = false);
	FileReportExporter(const FileReportExporter& other);


	std::string GetFilePath() const;
	void SetFilePath(const std::string& value);
	std::string GetTitle() const;
	void SetTitle(const std::string& value);
	std::string GetBody() const;
	void SetBody(const std::string& value);
	bool GetIncludeDate() const;
	void SetIncludeDate(bool value);
};
