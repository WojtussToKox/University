#include "Node.h"
#include "AlgebraicTree.h"
#include <cctype>
#include <iostream>


bool Node::isNumber(std::string token)
{
	if (token.empty()) return false;
	for (int i = 0; i < token.size(); i++) {
		if (!std::isdigit(token[i])) return false;
	}
	return true;
}


Node::Node()
{
	//pChildrenVector = {}; To podobno nowa rzecz dodana w c++11 i ma siê samo inicjalizowaæ
	value = "1";
	nodeType = TYPE_NUMBER;
	pParent = NULL;
	pTree = NULL;
	
}

Node::Node(std::string inputValue, bool& modified)
{
	//pChildrenVector = {};
	value = inputValue;
	pParent = NULL;
	pTree = NULL;
	
	if (value == AlgebraicTree::DEF_SUM || value == AlgebraicTree::DEF_DIFFERENCE || value == AlgebraicTree::DEF_MULT || value == AlgebraicTree::DEF_DIVISION) {
		nodeType = TYPE_OPERATOR_2_ARG;
	}
	else if (value == AlgebraicTree::DEF_SIN || value == AlgebraicTree::DEF_COS) {
		nodeType = TYPE_OPERATOR_1_ARG;
	}
	else if (isNumber(value)) {
		nodeType = TYPE_NUMBER;
	}
	else {
		
		std::string sanitizedValue = "";

		// Pêtla do oczyszczania tokenu (np. "a&b" -> "ab")
		for (int i = 0; i < value.size(); i++) {
			if (std::isalpha(value[i]) || std::isdigit(value[i])) {
				sanitizedValue += value[i];
			}
			else {
				modified = true; // ZnaleŸliœmy niedozwolony znak
			}
		}
		if (sanitizedValue == "") {
			value = "1";
			nodeType = TYPE_NUMBER;
		}
		else if (isNumber(sanitizedValue)) {
			value = sanitizedValue; // U¿ywamy oczyszczonej wartoœci token by³ "123$" -> "123"
			nodeType = TYPE_NUMBER;
		}
		else {
			value = sanitizedValue;
			nodeType = TYPE_VARIABLE;
		}
	}
}

Node::Node(std::string inputValue)
{
	//pChildrenVector = {};
	value = inputValue;
	pParent = NULL;
	pTree = NULL;

	if (value == AlgebraicTree::DEF_SUM || value == AlgebraicTree::DEF_DIFFERENCE || value == AlgebraicTree::DEF_MULT || value == AlgebraicTree::DEF_DIVISION) {
		nodeType = TYPE_OPERATOR_2_ARG;
	}
	else if (value == AlgebraicTree::DEF_SIN || value == AlgebraicTree::DEF_COS) {
		nodeType = TYPE_OPERATOR_1_ARG;
	}
	else if (isNumber(value)) {
		nodeType = TYPE_NUMBER;
	}
	else {
		// Jeœli nie jest operatorem ani liczb¹, to musi byæ zmienna
		nodeType = TYPE_VARIABLE;
	}
}

Node::~Node()
{
	for (int i = 0; i < pChildrenVector.size(); i++) {
		delete pChildrenVector[i];
	}
	
}

Node::eNodeType Node::getType()
{
	return nodeType;
}

void Node::addChild(Node* pNewChild)
{
	pChildrenVector.push_back(pNewChild);
	if (pNewChild != NULL) {
		pNewChild->setParent(this);
	}
}

std::string Node::getValue()
{
	return value;
}

int Node::getChildCount()
{
	return pChildrenVector.size();
}

Node* Node::getChild(int index)
{
	return pChildrenVector[index];
}

void Node::setChild(int index, Node* pNewChild)
{
	if (index >= 0 && index < pChildrenVector.size()) {
		delete pChildrenVector[index]; // Usuñ stary wêze³/poddrzewo
		pChildrenVector[index] = pNewChild;
		if (pNewChild != NULL) {
			pNewChild->setParent(this); // Ustaw rodzica dla nowego wêz³a
		}
	}
}

void Node::setParent(Node* pNewParent)
{
	pParent = pNewParent;
}

Node* Node::getParent()
{
	return pParent;
}

void Node::setTree(AlgebraicTree* pNewTree)
{
	pTree = pNewTree;
}

AlgebraicTree* Node::getTree()
{
	return pTree;
}