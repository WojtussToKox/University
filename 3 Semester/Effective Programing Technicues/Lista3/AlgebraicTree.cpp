#include "AlgebraicTree.h"
#include <sstream>
#include <cmath>
#include <cstdlib>
#include "Error.h"
#include <iostream>
#include <cctype>

const std::string AlgebraicTree::DEF_SUM = "+";
const std::string AlgebraicTree::DEF_DIFFERENCE = "-";
const std::string AlgebraicTree::DEF_MULT = "*";
const std::string AlgebraicTree::DEF_DIVISION = "/";

const std::string AlgebraicTree::DEF_SIN = "sin";
const std::string AlgebraicTree::DEF_COS = "cos";

const char AlgebraicTree::DEF_SEPERATOR = ' ';



AlgebraicTree::AlgebraicTree()
{
	pRoot = NULL;
}

AlgebraicTree::~AlgebraicTree()
{
	delete pRoot;
}

bool AlgebraicTree::buildTreeFromFormula(std::string formula)
{
	delete pRoot;
	pRoot = NULL;

	variables.clear();

	int offset = 0;
	bool modified = false;
	pRoot = buildTreeRecursivly(formula, offset, modified, NULL);

	
	if (pRoot != NULL) {
		getVariablesRecursivly(pRoot, variables);
	}

	while (offset < formula.size() && formula[offset] == ' ') {
		offset++;
	}

	if (offset < formula.size()) {
		modified = true;
	}

	return modified;
}

Node* AlgebraicTree::buildTreeRecursivly(std::string formula, int& offset, bool& modified, Node* pParentNode)
{
	if (offset >= formula.size()) {
		modified = true;
		Node* pDefaultNode = new Node();
		pDefaultNode->setParent(pParentNode);
		pDefaultNode->setTree(this);
		return pDefaultNode;
	}

	while (offset < formula.size() && formula[offset] == DEF_SEPERATOR) {
		offset++;
	}

	std::string actToken = "";
	while (offset < formula.size() && formula[offset] != DEF_SEPERATOR) {
		actToken += formula[offset++];
	}

	

	Node* pNewNode = new Node(actToken, modified);
	pNewNode->setParent(pParentNode);
	pNewNode->setTree(this);


	int childrenCount = 0;

	if (pNewNode->getType() == Node::TYPE_OPERATOR_2_ARG) {
		childrenCount = 2;
	}
	else if (pNewNode->getType() == Node::TYPE_OPERATOR_1_ARG) {
		childrenCount = 1;
	}

	for (int i = 0; i < childrenCount; i++) {
		Node* pChild = buildTreeRecursivly(formula, offset, modified, pNewNode);
		pNewNode->addChild(pChild);
	}
	
	return pNewNode;
}



std::string AlgebraicTree::toStringTree()
{
	std::string result;
	if (pRoot != NULL) {
		toStringTreeRecursivly(pRoot, result);
	}
	else {
		result = "AKTUALNIE BRAK ZAPISANEJ FORMULY W DRZEWIE";
	}
	return result;
}

void AlgebraicTree::toStringTreeRecursivly(Node* pNode, std::string& result)
{
	result += pNode->getValue() + " ";

	for (int i = 0; i < pNode->getChildCount(); i++) {
		toStringTreeRecursivly(pNode->getChild(i), result);
	}
}



std::vector<std::string> AlgebraicTree::getVariables()
{
	return variables;
}

void AlgebraicTree::getVariablesRecursivly(Node* pNode, std::vector<std::string>& variables)
{
	if (pNode->getType() == Node::TYPE_VARIABLE) {
		std::string varName = pNode->getValue();

		bool found = false;
		for (int i = 0; i < variables.size() && !found; i++) {
			if (varName == variables[i]) {
				found = true;
			}
		}
		if (!found) {
			variables.push_back(varName);
		}
	}

	for (int i = 0; i < pNode->getChildCount(); i++) {
		getVariablesRecursivly(pNode->getChild(i), variables);
	}
}

double AlgebraicTree::computeFormula(std::string values, Error& error)
{
	if (pRoot == NULL) {
		error.setError(Error::EMPTY_TREE, "Blad: Drzewo jest puste"); 
		return 0.0;
	}
	std::vector<std::string> vNames = getVariables();

	std::vector<double> vValues;
	std::stringstream ss(values);
	std::string value;

	while (ss >> value) {
		if (isStringNumber(value)) {
			// Jeœli jest poprawny, konwertujemy (atof jest OK, bo string jest ju¿ sprawdzony)
			vValues.push_back(atof(value.c_str()));
		}
		else {
			// Jeœli token nie jest liczb¹, ustaw b³¹d i przerwij
			std::stringstream ssError;
			ssError << "Blad: Niepoprawna wartosc w liscie argumentow: '" << value << "'. Oczekiwano liczby.";
			error.setError(Error::INVALID_ARGS, ssError.str());
			return 0.0; // Przerwij obliczenia
		}
	}

	if (vValues.size() != vNames.size()) {
		std::stringstream ssError;
		ssError << "Blad: Niewlasciwa liczba argumentow. Oczekiwano: " << vNames.size() << ", Podano: " << vValues.size();
		error.setError(Error::INVALID_ARGS, ssError.str()); 
		return 0.0;
	}

	std::map<std::string, double> mVariables;
	for (int i = 0; i < vNames.size(); i++) {
		mVariables[vNames[i]] = vValues[i];
	}

	return computeFormulaRecursivly(pRoot, mVariables, error);;
}



double AlgebraicTree::computeFormulaRecursivly(Node* pNode, std::map<std::string, double>& variablesMap, Error& error)
{
	if (error.hasError()) return 0.0;

	Node::eNodeType nodeType = pNode->getType();
	std::string value = pNode->getValue();

	switch (nodeType) 
	{
		case Node::TYPE_NUMBER:
			return atof(value.c_str());

		case Node::TYPE_VARIABLE:
			return variablesMap[value];

		case Node::TYPE_OPERATOR_1_ARG: {
			double childValue = computeFormulaRecursivly(pNode->getChild(0), variablesMap, error);
			
			

			if (value == DEF_SIN) return sin(childValue);
			if (value == DEF_COS) return cos(childValue);
			break;
		}
			
		case Node::TYPE_OPERATOR_2_ARG: {
			double leftChildValue = computeFormulaRecursivly(pNode->getChild(0), variablesMap, error);
			double rigthChildValue = computeFormulaRecursivly(pNode->getChild(1), variablesMap, error);
			if (value == DEF_SUM) return leftChildValue + rigthChildValue;
			if (value == DEF_DIFFERENCE) return leftChildValue - rigthChildValue;
			if (value == DEF_MULT) return leftChildValue * rigthChildValue;
			if (value == DEF_DIVISION) {
				if (rigthChildValue == 0) {
					error.setError(Error::COMPUTATION_ERROR, "Blad: Dzielenie przez 0!");
					if (error.hasError()) return 0.0;

				}
				return leftChildValue / rigthChildValue;
			}
			break;
		}
			
	}
	return 0.0;
}

AlgebraicTree::AlgebraicTree(const AlgebraicTree& otherTree)
{
	this->pRoot = NULL;
	this->pRoot = copyNodeRecursivly(otherTree.pRoot, NULL, this);

	
	this->variables.clear();
	if (this->pRoot != NULL) {
		getVariablesRecursivly(this->pRoot, this->variables);
	}
}

Node* AlgebraicTree::copyNodeRecursivly(Node* pOtherNode, Node* pParent, AlgebraicTree* pNewTree)
{
	if (pOtherNode == NULL) {
		return NULL;
	}

	// Stwórz nowy wêze³, kopiuj¹c wartoœæ
	Node* pNewNode = new Node(pOtherNode->getValue());
	pNewNode->setParent(pParent);
	pNewNode->setTree(pNewTree); // Ustaw wskaŸnik na nowe drzewo

	// Rekursywnie skopiuj dzieci
	for (int i = 0; i < pOtherNode->getChildCount(); i++) {
		Node* pNewChild = copyNodeRecursivly(pOtherNode->getChild(i), pNewNode, pNewTree);
		pNewNode->addChild(pNewChild);
	}

	return pNewNode;
}

Node* AlgebraicTree::findFirstLeaf(Node* pNode)
{
	if (pNode == NULL) {
		return NULL;
	}

	if (pNode->getChildCount() == 0) {
		return pNode;
	}
	
	for (int i = 0; i < pNode->getChildCount(); i++) {
		Node* pLeaf = findFirstLeaf(pNode->getChild(i));
		if (pLeaf != NULL) {
			return pLeaf; 
		}
	}

	return NULL; //Brak wêz³a bez lisci w teorii nigdy nie mo¿liwe do spe³nienia
}

bool AlgebraicTree::isStringNumber(std::string token)
{
	if (token.empty()) return false;
	for (int i = 0; i < token.size(); i++) {
		if (!std::isdigit(token[i])) return false;
	}
	return true;
}

AlgebraicTree& AlgebraicTree::operator=(const AlgebraicTree& otherTree)
{
	if (this == &otherTree) {
		return *this;
	}

	
	delete pRoot;
	pRoot = NULL;
	variables.clear();

	
	pRoot = copyNodeRecursivly(otherTree.pRoot, NULL, this);

	
	if (pRoot != NULL) {
		getVariablesRecursivly(pRoot, variables);
	}

	return *this;	
}

AlgebraicTree AlgebraicTree::operator+(const AlgebraicTree& otherTree) const
{
	
	AlgebraicTree newTree(*this);

	// Prawe puste zwroc lewe
	if (otherTree.pRoot == NULL) {
		return newTree;
	}

	// Lewe puste zwroc prawe
	if (newTree.pRoot == NULL) {
		AlgebraicTree newTreeCopy(otherTree);
		return newTreeCopy;
	}

	
	Node* pLeafToReplace = newTree.findFirstLeaf(newTree.pRoot);


	Node* pParent = pLeafToReplace->getParent();

	
	Node* pNewSubtreeRoot = newTree.copyNodeRecursivly(otherTree.pRoot, pParent, &newTree);

	//Przypadek 1: Liœæ by³ korzeniem
	if (pParent == NULL) {
		delete newTree.pRoot;
		newTree.pRoot = pNewSubtreeRoot; 
	}
	//Przypadek 2: Liœæ by³ dzieckiem
	else {
		// ZnajdŸ, którym dzieckiem by³ liœæ
		int childIndex = -1;

		for (int i = 0; i < pParent->getChildCount(); i++) {
			if (pParent->getChild(i) == pLeafToReplace) {
				childIndex = i;
			}
		}

		if (childIndex != -1) {
			
			pParent->setChild(childIndex, pNewSubtreeRoot);
		}
	}

	
	newTree.variables.clear();
	newTree.getVariablesRecursivly(newTree.pRoot, newTree.variables);

	
	return newTree;
}