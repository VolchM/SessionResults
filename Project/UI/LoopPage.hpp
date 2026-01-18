#pragma once

#include "UI/IPage.hpp"


class LoopPage : public IPage {
private:
	bool m_looping;

public:
	void Start() override;

protected:
	virtual void Loop() = 0;

	void StopLoop();
};
