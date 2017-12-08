#include "TreeManager.h"

TreeManager::TreeManager() {
	currentTree = nullptr;
}

TreeManager::~TreeManager() {
	if (currentTree != nullptr) {
		delete currentTree;
	}
}

int TreeManager::createNewTree(std::string formula) {
	if (currentTree != nullptr) {
		delete currentTree;
	}
	currentTree = new Tree();
	int errorCode = currentTree->parseExpression(formula);
	if (errorCode == ERROR_WHILE_PARSING_FORMULA) {
		return ERROR_WHILE_PARSING_FORMULA;
	}
	else return SUCCESS;
}

std::string TreeManager::getVars() {
	return currentTree == nullptr ? MSG_ERROR_TREE_NOT_CREATED : currentTree->vars();
}

std::string TreeManager::printTree() {
	return currentTree == nullptr ? MSG_ERROR_TREE_NOT_CREATED : currentTree->printONPFormula();
}

int TreeManager::computeValue(std::vector<int> environment, double &result) {
	if (currentTree == nullptr) {
		return ERROR_TREE_NOT_CREATED;
	}
	else {
		return currentTree->computeValue(&environment, result);
	}
}

int TreeManager::joinNewTree(std::string formula) {
	if (currentTree == nullptr) {
		return ERROR_TREE_NOT_CREATED;
	}
	else {
		Tree *oldTree = currentTree;
		Tree newTree;
		int errorCode = newTree.parseExpression(formula);
		currentTree = new Tree();
		*currentTree = *oldTree + newTree;
		delete oldTree;
		return errorCode;
	}
}


