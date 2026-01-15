#pragma once

#include "GroupTable/ITextTableRenderer.hpp"


class StyledTextTableRenderer : public ITextTableRenderer {
public:
	static const int MIN_COLUMN_WIDTH = 1;
	static const int RESULT_COLUMN_WIDTH = 3;
	static const int CELL_PADDING = 1;

protected:
	// Символы, используемые для создания таблицы
	char m_crossSymbol;
	char m_horizontalSymbol;
	char m_verticalSymbol;

public:
	StyledTextTableRenderer(char crossSymbol, char horizontalSymbol, char verticalSymbol);
	StyledTextTableRenderer(const StyledTextTableRenderer& other);


	char GetCrossSymbol() const;
	char GetHorizontalSymbol() const;
	char GetVerticalSymbol() const;

	std::string RenderTable(const GroupTableData& data) override;

	static std::unique_ptr<StyledTextTableRenderer> GetDefault();

protected:
	static std::vector<int> CalculateColumnWidths(GroupTableData data);
	static std::string TableSeparator(const std::vector<int>& widths, char crossSymbol, char horizontalSymbol);
	static std::string TableRow(const std::vector<std::string>& cells, const std::vector<int>& widths, char verticalSymbol);
};
