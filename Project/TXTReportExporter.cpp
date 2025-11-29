#include "TXTReportExporter.hpp"

#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>


std::vector<int> TXTReportExporter::CalculateColumnWidths(GroupTableData data) {
	std::vector<int> widths(data.GetDisciplines().size() + GroupTableData::EXTRA_COLUMNS_COUNT, MIN_COLUMN_WIDTH);
	widths[0] = std::max(widths[0], static_cast<int>(GroupTableData::FIO_COLUMN_HEADER.length()));
	for (auto& student : data.GetStudents()) {
		widths[0] = std::max(widths[0], static_cast<int>(student->GetLastNameWithInitials().length()));
	}
	for (int i = 1; i <= data.GetDisciplines().size(); i++) {
		widths[i] = std::max(widths[i], RESULT_COLUMN_WIDTH);
	}
	widths.back() = std::max(widths.back(), static_cast<int>(GroupTableData::AVERAGE_COLUMN_HEADER.length()));

	return widths;
}

std::string TXTReportExporter::TableSeparator(const std::vector<int>& widths, char crossSymbol, char horizontalSymbol) {
	std::string separator(1, crossSymbol);
	for (int width : widths) {
		separator.append(width + CELL_PADDING * 2, horizontalSymbol);
		separator.push_back(crossSymbol);
	}
	return separator;
}

std::string TXTReportExporter::TableRow(const std::vector<std::string>& cells, const std::vector<int>& widths, char verticalSymbol) {
	std::string row(1, verticalSymbol);
	for (int i = 0; i < widths.size(); i++) {
		row.append(CELL_PADDING, ' ');
		row.append(std::max(0, static_cast<int>(widths[i] - cells[i].length())), ' ');
		row.append(cells[i]);
		row.append(CELL_PADDING, ' ');
		row.push_back(verticalSymbol);
	}
	return row;
}



TXTReportExporter::TXTReportExporter(const std::string& filePath, const std::string& title, const std::string& body, bool includeDate) :
	FileReportExporter(filePath, title, body, includeDate) {}

TXTReportExporter::TXTReportExporter(const TXTReportExporter& other):
	FileReportExporter(other) {}

TXTReportExporter::~TXTReportExporter() {
	std::cout << "TXTReportExporter(filePath='" << m_filePath << "') destructor called" << std::endl;
}

void TXTReportExporter::Export(const GroupTable& groupTable) {
	GroupTableData data = groupTable.GetTableData();
	

	std::ofstream fout(m_filePath);

	if (!m_title.empty()) {
		fout << m_title << std::endl << std::endl;
	}
	if (!m_body.empty()) {
		fout << m_body << std::endl << std::endl;
	}
	if (m_includeDate) {
		time_t now = time(0);
		std::tm tmNow;
		localtime_s(&tmNow, &now);
		fout << "Дата генерации: " << std::put_time(&tmNow, "%d.%m.%Y") << std::endl << std::endl;
	}

	fout << RenderTable(data) << std::endl;
	fout << std::endl;

	for (int i = 0; i < data.GetDisciplines().size(); i++) {
		fout << (i+1) << " - " << data.GetDisciplines()[i]->GetName() << std::endl;
	}
}

std::string TXTReportExporter::RenderTable(const GroupTableData& data) {
	std::vector<int> widths = CalculateColumnWidths(data);
	std::string separator = TableSeparator(widths, TABLE_CROSS_SYMBOL, TABLE_HORIZONTAL_SYMBOL);

	std::stringstream ss;

	ss << separator << std::endl;
	ss << TableRow(data.TableHeader(), widths, TABLE_VERTICAL_SYMBOL) << std::endl;
	ss << separator << std::endl;
	for (const std::vector<std::string> &row : data.TableBodyToStrings(true)) {
		ss << TableRow(row, widths, TABLE_VERTICAL_SYMBOL) << std::endl;
	}
	ss << separator << std::endl;
	ss << TableRow(data.TableDisciplineAverages(), widths, TABLE_VERTICAL_SYMBOL) << std::endl;
	ss << separator;

	return ss.str();
}
