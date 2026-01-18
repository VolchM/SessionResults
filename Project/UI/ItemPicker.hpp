#pragma once

#include "UI/BaseItemPicker.hpp"

#include <string>
#include <vector>


class ItemPicker : public BaseItemPicker {
public:
	ItemPicker(const std::vector<std::string>& items);

protected:
	int GetInput() override;
};