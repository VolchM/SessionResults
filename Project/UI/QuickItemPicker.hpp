#pragma once

#include "UI/BaseItemPicker.hpp"

class QuickItemPicker : public BaseItemPicker {
public:
	QuickItemPicker(const std::vector<std::string>& items);

protected:
	int GetInput() override;
};

