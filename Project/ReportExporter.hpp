#pragma once

#include "GroupTable.hpp"

#include <string>


// Абстрактный класс для экспорта отчёта
class ReportExporter {
protected:
	std::string m_filePath; // Путь к файлу для сохранения отчёта
	std::string m_title; // Заголовок отчета
	std::string m_body; // Текст отчета
	bool m_includeDate; // Включать ли дату генерации в отчет

public:
	ReportExporter(const std::string& filePath, const std::string& title = "", const std::string& body = "", bool includeDate = false);
	ReportExporter(const ReportExporter& other);


	std::string GetFilePath();
	void SetFilePath(const std::string& value);
	std::string GetTitle();
	void SetTitle(const std::string& value);
	std::string GetBody();
	void SetBody(const std::string& value);
	bool GetIncludeDate();
	void SetIncludeDate(bool value);

	// Экспортирует таблицу группы
	virtual void Export(const GroupTable& groupTable) = 0;
};

