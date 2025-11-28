#include "StyledTXTReportExporter.hpp"

#include <sstream>

StyledTXTReportExporter::StyledTXTReportExporter(const std::string& filePath, const TableStyle& style, const std::string& title, const std::string& body, bool includeDate)
	:TXTReportExporter(filePath, title, body, includeDate), m_tableStyle(style) {}

StyledTXTReportExporter::StyledTXTReportExporter(const StyledTXTReportExporter& other) :
	TXTReportExporter(other), m_tableStyle(other.m_tableStyle) {}


const TableStyle & StyledTXTReportExporter::GetTableStyle() const {
	return m_tableStyle;
}

void StyledTXTReportExporter::SetTableStyle(const TableStyle& style) {
	m_tableStyle = style;
}

std::string StyledTXTReportExporter::RenderTable(const GroupTableData& data) {
	std::vector<int> widths = CalculateColumnWidths(data);
	std::string separator = TableSeparator(widths, m_tableStyle.GetCrossSymbol(), m_tableStyle.GetHorizontalSymbol());

	std::stringstream ss;

	ss << separator << std::endl;
	ss << TableRow(data.TableHeader(), widths, m_tableStyle.GetVerticalSymbol()) << std::endl;
	ss << separator << std::endl;
	for (const std::vector<std::string> &row : data.TableBodyToStrings(true)) {
		ss << TableRow(row, widths, m_tableStyle.GetVerticalSymbol()) << std::endl;
	}
	ss << separator << std::endl;
	ss << TableRow(data.TableDisciplineAverages(), widths, m_tableStyle.GetVerticalSymbol()) << std::endl;
	ss << separator;

	return ss.str();
}
