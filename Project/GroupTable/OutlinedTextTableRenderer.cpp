#include "GroupTable/OutlinedTextTableRenderer.hpp"

#include <sstream>

OutlinedTextTableRenderer::OutlinedTextTableRenderer(char crossSymbol, char horizontalSymbol, char verticalSymbol) :
	StyledTextTableRenderer(crossSymbol, horizontalSymbol, verticalSymbol) {}

OutlinedTextTableRenderer::OutlinedTextTableRenderer(const OutlinedTextTableRenderer& other) :
	StyledTextTableRenderer(other) {}

std::string OutlinedTextTableRenderer::RenderTable(const GroupTableData& data) {
    std::string table = StyledTextTableRenderer::RenderTable(data);
    int width = table.find('\n');
    std::string outline = m_crossSymbol + std::string(width, m_horizontalSymbol) + m_crossSymbol;

    std::stringstream resultss;

    std::stringstream tabless(table);
    std::string buf;
    resultss << outline << std::endl;
    while (std::getline(tabless, buf)) {
        resultss << m_verticalSymbol << buf << m_verticalSymbol << std::endl;
    }
    resultss << outline;

    return resultss.str();
}

std::unique_ptr<OutlinedTextTableRenderer> OutlinedTextTableRenderer::GetDefault() {
    return std::make_unique<OutlinedTextTableRenderer>('+', '-', '|');
}
