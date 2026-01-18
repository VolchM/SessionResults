#pragma once

#include "Data/Faculty.hpp"
#include "UI/IPage.hpp"
#include "GroupTable/GroupTable.hpp"

#include <memory>
#include <string>
#include <tuple>


class GroupTablePage : public IPage {
private:
	std::shared_ptr<Faculty> m_faculty;

public:
	GroupTablePage(std::shared_ptr<Faculty> faculty);

	void Start() override;

private:
	GroupTable CreateGroupTable();
	void PrintTable(const GroupTable& groupTable);
	void ExportToTXT(const GroupTable& groupTable);
	std::tuple<std::string, std::string, std::string, bool> GetReportExportData(const std::string& fileExtension);
};