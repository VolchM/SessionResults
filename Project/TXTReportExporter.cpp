#include "TXTReportExporter.hpp"

#include <fstream>
#include <chrono>
#include <iomanip>


const char TABLE_CROSS_SYMBOL = '+';
const char TABLE_HORIZONTAL_SYMBOL = '-';
const char TABLE_VERTICAL_SYMBOL = '|';

const std::string FIO_COLUMN_HEADER = "ФИО";
const std::string AVERAGE_COLUMN_HEADER = "Средний балл";
const int EXTRA_COLUMNS_COUNT = 2;

const int MIN_COLUMN_WIDTH = 1;
const int RESULT_COLUMN_WIDTH = 3;
const int CELL_PADDING = 1;


std::vector<int> TXTReportExporter::CalculateColumnWidths(GroupTableData data) {
	std::vector<int> widths(data.GetDisciplines().size() + EXTRA_COLUMNS_COUNT, MIN_COLUMN_WIDTH);
	widths[0] = std::max(widths[0], static_cast<int>(FIO_COLUMN_HEADER.length()));
	for (auto& student : data.GetStudents()) {
		widths[0] = std::max(widths[0], static_cast<int>(student->GetLastNameWithInitials().length()));
	}
	for (int i = 1; i <= data.GetDisciplines().size(); i++) {
		widths[i] = std::max(widths[i], RESULT_COLUMN_WIDTH);
	}
	widths.back() = std::max(widths.back(), static_cast<int>(AVERAGE_COLUMN_HEADER.length()));

	return widths;
}

std::string TXTReportExporter::TableSeparator(const std::vector<int>& widths) {
	std::string separator(1, TABLE_CROSS_SYMBOL);
	for (int width : widths) {
		separator.append(width + CELL_PADDING * 2, TABLE_HORIZONTAL_SYMBOL);
		separator.push_back(TABLE_CROSS_SYMBOL);
	}
	return separator;
}

std::string TXTReportExporter::TableRow(const std::vector<std::string>& cells, const std::vector<int>& widths) {
	std::string row(1, TABLE_VERTICAL_SYMBOL);
	for (int i = 0; i < widths.size(); i++) {
		row.append(CELL_PADDING, ' ');
		row.append(std::max(0, static_cast<int>(widths[i] - cells[i].length())), ' ');
		row.append(cells[i]);
		row.append(CELL_PADDING, ' ');
		row.push_back(TABLE_VERTICAL_SYMBOL);
	}
	return row;
}

std::string TXTReportExporter::TableHeader(const GroupTableData& data, const std::vector<int>& widths) {
	std::vector<std::string> cells;
	cells.push_back(FIO_COLUMN_HEADER);
	for (int i = 1; i <= data.GetDisciplines().size(); i++) {
		cells.push_back(std::to_string(i));
	}
	cells.push_back(AVERAGE_COLUMN_HEADER);

	return TableRow(cells, widths);
}

std::vector<std::string> TXTReportExporter::TableBodyToStrings(const GroupTableData& data, const std::vector<int>& widths) {
	std::vector<std::string> result;

	std::vector<int> studentAverages = data.StudentAverages();
	for (int i = 0; i < data.GetStudents().size(); i++) {
		std::vector<std::string> cells(data.GetDisciplines().size() + 2);

		cells[0] = data.GetStudents()[i]->GetLastNameWithInitials();
		for (int j = 0; j < data.GetDisciplines().size(); j++) {
			const std::shared_ptr<AttestationResult>& res = data.GetTableBody()[i][j];
			cells[j + 1] = res ? res->ToStringCompact() : "";
		}
		cells.back() = std::to_string(studentAverages[i]);

		result.push_back(TableRow(cells, widths));
	}

	return result;
}

std::string TXTReportExporter::TableDisciplineAverages(const GroupTableData& data, const std::vector<int>& widths) {
	std::vector<std::string> cells;
	cells.push_back("");
	for (int average : data.DisciplineAverages()) {
		cells.push_back(std::to_string(average));
	}
	cells.push_back(std::to_string(data.GroupAverage()));

	return TableRow(cells, widths);
}

TXTReportExporter::TXTReportExporter(const std::string& filePath, const std::string& title, const std::string& body, bool includeDate) :
	ReportExporter(filePath, title, body, includeDate) {}

TXTReportExporter::TXTReportExporter(const TXTReportExporter& other):
	ReportExporter(other) {}

void TXTReportExporter::Export(const GroupTable& groupTable) {
	GroupTableData data = groupTable.GetTableData();
	std::vector<int> widths = CalculateColumnWidths(data);
	std::string separator = TableSeparator(widths);

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

	fout << separator << std::endl;
	fout << TableHeader(data, widths) << std::endl;
	fout << separator << std::endl;
	for (const std::string &row : TableBodyToStrings(data, widths)) {
		fout << row << std::endl;
	}
	fout << separator << std::endl;
	fout << TableDisciplineAverages(data, widths) << std::endl;
	fout << separator << std::endl;

	fout << std::endl;

	for (int i = 0; i < data.GetDisciplines().size(); i++) {
		fout << (i+1) << " - " << data.GetDisciplines()[i]->GetName() << std::endl;
	}
}
