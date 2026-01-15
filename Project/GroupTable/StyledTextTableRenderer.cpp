#include "GroupTable/StyledTextTableRenderer.hpp"

#include <sstream>


StyledTextTableRenderer::StyledTextTableRenderer(char crossSymbol, char horizontalSymbol, char verticalSymbol) :
	m_crossSymbol(crossSymbol), m_horizontalSymbol(horizontalSymbol), m_verticalSymbol(verticalSymbol) {}

StyledTextTableRenderer::StyledTextTableRenderer(const StyledTextTableRenderer& other) :
	m_crossSymbol(other.m_crossSymbol), m_horizontalSymbol(other.m_horizontalSymbol), m_verticalSymbol(other.m_verticalSymbol) {}

char StyledTextTableRenderer::GetCrossSymbol() const {
	return m_crossSymbol;
}

char StyledTextTableRenderer::GetHorizontalSymbol() const {
	return m_horizontalSymbol;
}

char StyledTextTableRenderer::GetVerticalSymbol() const {
	return m_verticalSymbol;
}

std::string StyledTextTableRenderer::RenderTable(const GroupTableData& data) {
	std::vector<int> widths = CalculateColumnWidths(data);
	std::string separator = TableSeparator(widths, m_crossSymbol, m_horizontalSymbol);

	std::stringstream ss;

	ss << separator << std::endl;
	ss << TableRow(data.TableHeader(), widths, m_verticalSymbol) << std::endl;
	ss << separator << std::endl;
	for (const std::vector<std::string> &row : data.TableBodyToStrings(true)) {
		ss << TableRow(row, widths, m_verticalSymbol) << std::endl;
	}
	ss << separator << std::endl;
	ss << TableRow(data.TableDisciplineAverages(), widths, m_verticalSymbol) << std::endl;
	ss << separator;

	return ss.str();
}

std::unique_ptr<StyledTextTableRenderer> StyledTextTableRenderer::GetDefault() {
	return std::make_unique<StyledTextTableRenderer>('+', '-', '|');
}

std::vector<int> StyledTextTableRenderer::CalculateColumnWidths(GroupTableData data) {
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

std::string StyledTextTableRenderer::TableSeparator(const std::vector<int>& widths, char crossSymbol, char horizontalSymbol) {
	std::string separator(1, crossSymbol);
	for (int width : widths) {
		separator.append(width + CELL_PADDING * 2, horizontalSymbol);
		separator.push_back(crossSymbol);
	}
	return separator;
}

std::string StyledTextTableRenderer::TableRow(const std::vector<std::string>& cells, const std::vector<int>& widths, char verticalSymbol) {
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
