#pragma once

#include "GroupTable/GroupTable.hpp"

class IReportExporter {
public:
	// Экспортирует таблицу группы
	virtual void Export(const GroupTable& groupTable) = 0;

	virtual ~IReportExporter() {}
};

