#include "UI/LoopPage.hpp"


void LoopPage::Start() {
	m_looping = true;
	while (m_looping) {
		Loop();
	}
}

void LoopPage::StopLoop() {
	m_looping = false;
}
