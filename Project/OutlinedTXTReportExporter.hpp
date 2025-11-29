#pragma once

#include "TXTReportExporter.hpp"

class OutlinedTXTReportExporter : public TXTReportExporter {
public:
	OutlinedTXTReportExporter(const std::string& filePath, const std::string& title = "", const std::string& body = "", bool includeDate = false);
	OutlinedTXTReportExporter(const OutlinedTXTReportExporter& other);
	OutlinedTXTReportExporter& operator=(const TXTReportExporter& other);

	std::string RenderTable(const GroupTableData& data) override;
};

