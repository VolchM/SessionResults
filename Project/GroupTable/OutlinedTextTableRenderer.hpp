#pragma once

#include "GroupTable/StyledTextTableRenderer.hpp"


class OutlinedTextTableRenderer : public StyledTextTableRenderer {
public:
	OutlinedTextTableRenderer(char crossSymbol, char horizontalSymbol, char verticalSymbol);
	OutlinedTextTableRenderer(const OutlinedTextTableRenderer& other);

	std::string RenderTable(const GroupTableData& data) override;

	static std::unique_ptr<OutlinedTextTableRenderer> GetDefault();
};

