#pragma once
#include "AlgebraicTree.h"
#include "Error.h"
#include <string>

class Interface
{
private:
	AlgebraicTree actTree;

	void handleEnter(std::string formula);
	void handlePrint();
	void handleVars();
	void handleComp(std::string values);
	void handleJoin(std::string formula);

public:
	static const std::string DEF_ENTER_COMMAND;
	static const std::string DEF_PRINT_COMMAND;
	static const std::string DEF_VARS_COMMAND;
	static const std::string DEF_COMP_COMMAND;
	static const std::string DEF_JOIN_COMMAND;
	static const std::string DEF_EXIT_COMMAND;
		
	Interface();

	void run();
};

