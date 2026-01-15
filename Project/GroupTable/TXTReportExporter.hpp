#pragma once

#include "GroupTable/FileReportExporter.hpp"
#include "GroupTable/GroupTableData.hpp"
#include "GroupTable/ITextTableRenderer.hpp"

#include <memory>


// Класс для экспорта отчёта в текстовый файл
class TXTReportExporter : public FileReportExporter {
private:
	std::unique_ptr<ITextTableRenderer> m_renderer;

public:
	TXTReportExporter(const std::string& filePath, std::unique_ptr<ITextTableRenderer> renderer, const std::string& title = "", const std::string& body = "", bool includeDate = false);
	TXTReportExporter(const TXTReportExporter& other);

	void Export(const GroupTable& groupTable) override;
};
