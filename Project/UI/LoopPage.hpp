#pragma once

#include "UI/IPage.hpp"
#include "UI/MenuActionPicker.hpp"


class LoopPage : public IPage {
private:
	bool m_looping;
	std::unique_ptr<MenuActionPicker> m_picker;

public:
	void Start() override;

protected:
	virtual void Loop() = 0;

	void StopLoop();

	void SetPicker(std::unique_ptr<MenuActionPicker> picker);
};
