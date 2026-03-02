#include "Interface.h"
#include <iostream>
#include <sstream>
#include <vector>

const std::string Interface::DEF_ENTER_COMMAND = "enter";
const std::string Interface::DEF_PRINT_COMMAND = "print";
const std::string Interface::DEF_VARS_COMMAND = "vars";
const std::string Interface::DEF_COMP_COMMAND = "comp";
const std::string Interface::DEF_JOIN_COMMAND = "join";
const std::string Interface::DEF_EXIT_COMMAND = "exit";

void Interface::handleEnter(std::string formula)
{
	if (actTree.buildTreeFromFormula(formula)) {
		std::cout << "Formula zmodyfikowana do postaci: ";
		handlePrint();
	}
	else {
		std::cout << "Poprawnie wpisano formule ";
	}
	std::cout << std::endl;
}

void Interface::handlePrint()
{
	std::cout << actTree.toStringTree() << "\n\n";
}

void Interface::handleVars()
{
	std::vector<std::string> vVars = actTree.getVariables();
	if (vVars.empty()) {
		std::cout << "Brak zmiennych w drzewie. \n";
	}
	else {
		std::cout << "Zmienne w drzewie: ";
		for (int i = 0; i < vVars.size(); i++) {
			std::cout << vVars[i] << " ";
		}
		std::cout << std::endl;
	}
}

void Interface::handleComp(std::string values)
{
	Error err;
	double dResult = actTree.computeFormula(values, err);
	
	if (!err.hasError()) {
		std::cout << "Wynik: " << dResult << std::endl;
	}
	else {
		std::cout << err.getMessage() << std::endl;
	}
}

void Interface::handleJoin(std::string formula)
{
	AlgebraicTree newTree;

	bool modified = newTree.buildTreeFromFormula(formula);

	if (modified) {
		std::cout << "Formula (join) zmodyfikowana do postaci: " << newTree.toStringTree() << std::endl;
	}

	actTree = actTree + newTree;
	std::cout << "Drzewa polaczone. Nowa formula: ";
	handlePrint();
}

Interface::Interface()
{
	AlgebraicTree newTree;
	actTree = newTree;
}

void Interface::run()
{
	std::string inputLine, command;

	bool exit = false;
	
	while (!exit) {

		std::cout << "Wpisz komende -> ";

		std::getline(std::cin, inputLine);

		//StringStream usuwa wiod¹ce spajce
		std::stringstream ss(inputLine);

		ss >> command;

		if (command == DEF_ENTER_COMMAND) {

			std::string formula;
			std::getline(ss, formula);
			handleEnter(formula);
		}

		else if (command == DEF_PRINT_COMMAND) {

			handlePrint();
		}

		else if (command == DEF_VARS_COMMAND) {
			handleVars();
		}

		else if (command == DEF_COMP_COMMAND) {
			std::string values;
			std::getline(ss, values);
			handleComp(values);
		}

		else if (command == DEF_JOIN_COMMAND) {
			std::string formula;
			std::getline(ss, formula);
			handleJoin(formula);
		}	

		else if (command == DEF_EXIT_COMMAND) {

			std::cout << "Wyjscie z programu \n";
			exit = true;

		}

		else {

			std::cout << "Nie rozpoznano komendy poczatkowej wpisz jeszcze raz \n";

		}
	}
}
