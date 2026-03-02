#pragma once
#include <string>
#include <vector>

class AlgebraicTree; // powiedzenie tej klasie ¿e drzewo faktycznie istnieje

class Node {

public: 

	enum eNodeType {
		TYPE_NUMBER,
		TYPE_VARIABLE,
		TYPE_OPERATOR_1_ARG,
		TYPE_OPERATOR_2_ARG
	};

private:
	std::string value;
	std::vector<Node*> pChildrenVector;
	eNodeType nodeType;

	Node* pParent; 
	AlgebraicTree* pTree;

	bool isNumber(std::string token);

public:

	Node();
	Node(std::string inputValue, bool& modified);
	Node(std::string inputValue);

	Node(const Node& other);           
	Node& operator=(const Node& other);

	~Node();
	eNodeType getType();

	void addChild(Node* pNewChild);
	void setChild(int index, Node* pNewChild);
	std::string getValue();
	int getChildCount();

	Node* getChild(int index);

	void setParent(Node* pParent);
	Node* getParent();
	void setTree(AlgebraicTree* pTree);
	AlgebraicTree* getTree();

};

