#pragma once
#include "Node.h"
#include <string>
#include <map>
#include <vector>
#include "Error.h"
#include <utility>

class AlgebraicTree
{
private:
	Node* pRoot;
	std::vector<std::string> variables;

	Node* buildTreeRecursivly(std::string formula, int& offset, bool& modified, Node* pParentNode);
	double computeFormulaRecursivly(Node* pNode, std::map<std::string, double>& variablesMap, Error& error);
	void toStringTreeRecursivly(Node* pNode, std::string& result);
	void getVariablesRecursivly(Node* pNode, std::vector<std::string>& variables);

	Node* copyNodeRecursivly(Node* pOtherNode, Node* pParent, AlgebraicTree* pNewTree);
	Node* findFirstLeaf(Node* pNode);
	bool isStringNumber(std::string token);

public:
	static const std::string DEF_SUM;
	static const std::string DEF_DIFFERENCE;
	static const std::string DEF_MULT;
	static const std::string DEF_DIVISION;

	static const std::string DEF_SIN;
	static const std::string DEF_COS;

	static const char DEF_SEPERATOR;

	AlgebraicTree();
	AlgebraicTree(const AlgebraicTree& otherTree);

	~AlgebraicTree();

	bool buildTreeFromFormula(std::string formula);
	std::string toStringTree();

	double computeFormula(std::string values, Error& error);
	std::vector<std::string> getVariables();


	AlgebraicTree& operator=(const AlgebraicTree& otherTree);
	AlgebraicTree operator+(const AlgebraicTree& otherTree) const;


	AlgebraicTree(AlgebraicTree&& otherTree);
	AlgebraicTree& operator=(AlgebraicTree&& otherTree);
};

