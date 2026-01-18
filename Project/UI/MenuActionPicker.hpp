#pragma once

#include "UI/QuickItemPicker.hpp"

#include <vector>
#include <functional>
#include <memory>

class MenuActionPicker {
public:
	using Item = std::pair<std::string, std::function<void()>>;

private:
	std::unique_ptr<QuickItemPicker> m_picker;
	std::vector<std::function<void()>> m_actions;

public:
	MenuActionPicker(const std::vector<std::string>& items, const std::vector<std::function<void()>>& actions);
	MenuActionPicker(const std::vector<Item>& items);

	void PickAndRun();
};
