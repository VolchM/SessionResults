#include "UI/MenuActionPicker.hpp"

#include <stdexcept>


MenuActionPicker::MenuActionPicker(const std::vector<std::string>& items, const std::vector<std::function<void()>>& actions) {
	m_picker = std::make_unique<QuickItemPicker>(items);
	m_actions = actions;
	if (m_picker->GetItemCount() != m_actions.size()) {
		throw std::invalid_argument("Item count is not equal to actions count");
	}
}

MenuActionPicker::MenuActionPicker(const std::vector<Item>& items) {
	std::vector<std::string> labels;
	std::vector<std::function<void()>> actions;

	for (auto p : items) {
		labels.push_back(p.first);
		actions.push_back(p.second);
	}

	m_picker = std::make_unique<QuickItemPicker>(labels);
	m_actions = actions;
}


void MenuActionPicker::PickAndRun() {
	int selectedIndex = m_picker->Pick();
	m_actions[selectedIndex]();
}
