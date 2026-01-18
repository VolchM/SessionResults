#pragma once

#include <string>
#include <vector>


class BaseItemPicker {
private:
	std::vector<std::string> m_items;

protected:
	int m_printedLines = 0;

public:
	BaseItemPicker(const std::vector<std::string>& items);

	int GetItemCount();

	int Pick();

protected:
	virtual int GetInput() = 0;

private:
	void PrintItems();
	void ClearOutput();
};
