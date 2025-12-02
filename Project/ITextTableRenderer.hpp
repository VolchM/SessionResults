#pragma once

#include "GroupTableData.hpp"


// Объект, преобразующий таблицу в текст
class ITextTableRenderer {
public:
	// Преобразует таблицу в текст
	virtual std::string RenderTable(const GroupTableData& data) = 0;

	virtual ~ITextTableRenderer() {}
};
