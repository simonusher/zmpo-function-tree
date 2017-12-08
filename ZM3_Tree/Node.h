#pragma once
#include <string>
#include <cstdlib>
#include "constants.h"
#include "stringOps.h"
#include <vector>
#include "Tree.h"
#include <cmath>
#include <cctype>
const enum NodeType {
	OperationSum,
	OperationSub,
	OperationMult,
	OperationDiv,
	OperationSin,
	OperationCos,
	Constant,
	Variable,
	Undefined
};

const std::string OPERATION_SUM = "+";
const std::string OPERATION_SUB = "-";
const std::string OPERATION_MULT = "*";
const std::string OPERATION_DIV = "/";
const std::string OPERATION_SIN = "sin";
const std::string OPERATION_COS = "cos";

const int DEFAULT_CONSTANT = 1;

class Node {
	friend class Tree;
public:
	Node(Tree* parentTree);
	Node(Node &otherNode, Tree* parentTree);
	~Node();
	int parseString(std::string &stringToParse, int startIndex);
	std::string printNodes();
	std::string printONPFormula();
private:
	void attachAtLeaf(Node &otherNode);
	void updateVariables();
	double computeValue();
	int nodeType;
	Tree *parentTree;
	std::vector<Node*> children;
	std::string variableName;
	int constantValue;
	bool removeForbiddenChars(std::string &expression);
	bool isNumber(const std::string &string);
};