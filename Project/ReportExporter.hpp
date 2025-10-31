#pragma once

#include "GroupTable.hpp"

#include <string>


// Абстрактный класс для экспорта отчёта
class ReportExporter {
public:
	// Экспортирует таблицу группы
	virtual void Export(const GroupTable& groupTable, std::string filename) = 0;
};

