#include "OutlinedTXTReportExporter.hpp"

#include <sstream>

OutlinedTXTReportExporter::OutlinedTXTReportExporter(const std::string& filePath, const std::string& title, const std::string& body, bool includeDate) :
    TXTReportExporter(filePath, title, body, includeDate) {}

OutlinedTXTReportExporter::OutlinedTXTReportExporter(const OutlinedTXTReportExporter& other) :
    TXTReportExporter(other) {}

OutlinedTXTReportExporter& OutlinedTXTReportExporter::operator=(const TXTReportExporter& other) {
    m_filePath = other.GetFilePath();
    m_title = other.GetTitle();
    m_body = other.GetBody();
    m_includeDate = other.GetIncludeDate();
    return *this;
}


std::string OutlinedTXTReportExporter::RenderTable(const GroupTableData& data) {
    std::string table = TXTReportExporter::RenderTable(data);
    int width = table.find('\n');
    std::string outline = TABLE_CROSS_SYMBOL + std::string(width, TABLE_HORIZONTAL_SYMBOL) + TABLE_CROSS_SYMBOL;

    std::stringstream resultss;

    std::stringstream tabless(table);
    std::string buf;
    resultss << outline << std::endl;
    while (std::getline(tabless, buf)) {
        resultss << TABLE_VERTICAL_SYMBOL << buf << TABLE_VERTICAL_SYMBOL << std::endl;
    }
    resultss << outline;

    return resultss.str();
}
