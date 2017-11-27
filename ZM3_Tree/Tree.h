#pragma once
#include "Node.h"

const std::string MSG_TREE_EMPTY = "The tree is empty.";
const std::string MSG_NO_VARIABLES = "The tree contains no variables.";
const std::string MSG_VARIABLES = "Variables: ";
class Tree {
public:
	friend class Node;
	Tree();
	Tree(Tree &otherTree);
	~Tree();
	void operator=(Tree &otherTree);
	int parseExpression(std::string &expression);
	std::string printNodes();
	void clear();
	std::string vars();
	double computeValue(std::vector<int> *environment);
private:
	int valueOfVariable(std::string &variableName);
	int indexOfVariable(std::string &variableName);
	std::vector<int> *environment;
	void addVariable(std::string);
	std::vector<std::string> variables;
	int errorCode;
	Node *root;
};