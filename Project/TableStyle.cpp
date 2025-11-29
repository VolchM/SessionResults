#include "TableStyle.hpp"

TableStyle::TableStyle(char crossSymbol, char horizontalSymbol, char verticalSymbol):
	m_crossSymbol(crossSymbol), m_horizontalSymbol(horizontalSymbol), m_verticalSymbol(verticalSymbol) {}

TableStyle::TableStyle(const TableStyle& other):
	m_crossSymbol(other.m_crossSymbol), m_horizontalSymbol(other.m_horizontalSymbol), m_verticalSymbol(other.m_verticalSymbol) {}

char TableStyle::GetCrossSymbol() const {
	return m_crossSymbol;
}

char TableStyle::GetHorizontalSymbol() const {
	return m_horizontalSymbol;
}

char TableStyle::GetVerticalSymbol() const {
	return m_verticalSymbol;
}
