#pragma once

#include "Data/Faculty.hpp"
#include "UI/IPage.hpp"
#include "UI/ResultsEditingPage.hpp"

#include <memory>


class ResultsSelectPage : public IPage {
private:
	std::shared_ptr<Faculty> m_faculty;

public:
	ResultsSelectPage(std::shared_ptr<Faculty> faculty);

	void Start() override;
};