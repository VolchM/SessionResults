#pragma once

#include "FileReportExporter.hpp"
#include "GroupTableData.hpp"


// Класс для экспорта отчёта в текстовый файл
class TXTReportExporter : public FileReportExporter {
public:
	static const char TABLE_CROSS_SYMBOL = '+';
	static const char TABLE_HORIZONTAL_SYMBOL = '-';
	static const char TABLE_VERTICAL_SYMBOL = '|';

	static const int MIN_COLUMN_WIDTH = 1;
	static const int RESULT_COLUMN_WIDTH = 3;
	static const int CELL_PADDING = 1;

protected:
	static std::vector<int> CalculateColumnWidths(GroupTableData data);
	static std::string TableSeparator(const std::vector<int>& widths, char crossSymbol, char horizontalSymbol);
	static std::string TableRow(const std::vector<std::string>& cells, const std::vector<int>& widths, char verticalSymbol);

public:
	TXTReportExporter(const std::string& filePath, const std::string& title = "", const std::string& body = "", bool includeDate = false);
	TXTReportExporter(const TXTReportExporter& other);

	void Export(const GroupTable& groupTable) override;

	// Преобразует таблицу в текст
	virtual std::string RenderTable(const GroupTableData& data);
};
