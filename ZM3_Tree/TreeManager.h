#pragma once
#include "Tree.h"
const std::string MSG_ERROR_TREE_NOT_CREATED = "Tree not yet created!";

class TreeManager {
public:
	TreeManager();
	~TreeManager();
	int createNewTree(std::string formula);
	std::string getVars();
	std::string printTree();
	int computeValue(std::vector<int> environment, double &result);
	int joinNewTree(std::string formula);
private:
	Tree *currentTree;
};
