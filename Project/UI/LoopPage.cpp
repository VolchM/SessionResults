#include "UI/LoopPage.hpp"

#include <iostream>


void LoopPage::Start() {
	m_looping = true;
	while (m_looping) {
		Loop();
		std::cout << "Действия:\n";
		if (m_picker != nullptr) {
			m_picker->PickAndRun();
		}
	}
}

void LoopPage::StopLoop() {
	m_looping = false;
}

void LoopPage::SetPicker(std::unique_ptr<MenuActionPicker> picker) {
	m_picker = std::move(picker);
}
