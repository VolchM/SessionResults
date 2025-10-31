#pragma once

#include "ReportExporter.hpp"


// Класс для экспорта отчёта в текстовый файл
class TXTReportExporter : public ReportExporter {
private:
	static std::vector<int> CalculateColumnWidths(GroupTableData data);
	static std::string TableSeparator(const std::vector<int>& widths);
	static std::string TableRow(const std::vector<std::string>& cells, const std::vector<int>& widths);
	static std::string TableHeader(const GroupTableData& data, const std::vector<int>& widths);
	static std::vector<std::string> TableBodyToStrings(const GroupTableData& data, const std::vector<int>& widths);
	static std::string TableDisciplineAverages(const GroupTableData& data, const std::vector<int>& widths);
public:
	void Export(const GroupTable& groupTable, std::string filename) override;
};

