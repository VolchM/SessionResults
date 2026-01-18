#include "UI/BaseItemPicker.hpp"

#include <iostream>
#include <format>


BaseItemPicker::BaseItemPicker(const std::vector<std::string>& items) {
	m_items = items;
}

int BaseItemPicker::GetItemCount() {
	return m_items.size();
}

int BaseItemPicker::Pick() {
    m_printedLines = 0;
    PrintItems();

    int selectedIndex = GetInput();

    ClearOutput();
    std::cout << std::format("{} - {}\n", selectedIndex + 1, m_items[selectedIndex]);

    return selectedIndex;
}

void BaseItemPicker::PrintItems() {
    for (int i = 0; i < m_items.size(); i++) {
        std::cout << std::format("{} - {}\n", i + 1, m_items[i]);
    }
    m_printedLines += m_items.size();
}

void BaseItemPicker::ClearOutput() {
    std::cout << "\u001b[" << m_printedLines << "F"; // Перемещает курсор вверх на m_printedLines строк
    std::cout << "\u001b[0J"; // Очищает консоль от курсора до конца экрана
}
