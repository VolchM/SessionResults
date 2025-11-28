#pragma once

#include "TXTReportExporter.hpp"
#include "TableStyle.hpp"



class StyledTXTReportExporter : public TXTReportExporter {
protected:
	TableStyle m_tableStyle;

public:
	StyledTXTReportExporter(const std::string& filePath, const TableStyle& style, const std::string& title = "", const std::string& body = "", bool includeDate = false);	
	StyledTXTReportExporter(const StyledTXTReportExporter& other);


	const TableStyle& GetTableStyle() const;
	void SetTableStyle(const TableStyle& style);

	std::string RenderTable(const GroupTableData& data) override;
};
