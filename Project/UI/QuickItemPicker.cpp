#include "UI/QuickItemPicker.hpp"

#include <iostream>
#include "conio.h"


QuickItemPicker::QuickItemPicker(const std::vector<std::string>& items) : BaseItemPicker(items) {
	if (GetItemCount() > 9) {
		throw std::invalid_argument("Maximum number of items is 9");
	}
}


int QuickItemPicker::GetInput() {
	std::cout << "Нажмите номер: ";

	while (true) {
		char c = _getch();
		int value = c - '1';

		if (value >= 0 && value < GetItemCount()) {
			return value;
		}
	}
}
