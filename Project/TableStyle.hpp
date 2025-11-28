#pragma once


// Стиль таблицы
class TableStyle {
private:
	char m_crossSymbol;
	char m_horizontalSymbol;
	char m_verticalSymbol;

public:
	TableStyle(char crossSymbol, char horizontalSymbol, char verticalSymbol);
	TableStyle(const TableStyle& other);

	char GetCrossSymbol() const;
	char GetHorizontalSymbol() const;
	char GetVerticalSymbol() const;
};

