#include "UI/ItemPicker.hpp"

#include <iostream>


ItemPicker::ItemPicker(const std::vector<std::string>& items) :
	BaseItemPicker(items) {}


int ItemPicker::GetInput() {
	int value;
	while (true) {
		std::cout << "Введите номер: ";
		m_printedLines++;
		if ((std::cin >> value) && (value >= 1 && value <= GetItemCount())) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return value - 1;
		} else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
}
