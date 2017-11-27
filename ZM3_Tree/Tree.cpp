#include "Tree.h"

Tree::Tree() {
	this->errorCode = SUCCESS;
	this->root = nullptr;

}

Tree::~Tree() {
	if (this->root != nullptr) {
		delete this->root;
	}
}

Tree::Tree(Tree &otherTree) {
	this->errorCode = SUCCESS;
	if (otherTree.root != nullptr) {
		this->root = new Node(*otherTree.root, this);
	}
	else {
		this->root = nullptr;
	}
}

void Tree::operator=(Tree &otherTree) {
	this->clear();
	if (otherTree.root != nullptr) {
		this->root = new Node(*otherTree.root, this);
	}
	else {
		this->root = nullptr;
	}
}



void Tree::clear() {
	if (this->root != nullptr) {
		delete this->root;
	}
	this->root = nullptr;
	this->variables.clear();
	this->errorCode = SUCCESS;
}

int Tree::parseExpression(std::string &expression) {
	this->clear();
	this->root = new Node(this);
	root->parseString(expression, 0);
	int currentErrorCode = this->errorCode;
	this->errorCode = SUCCESS;
	return this->errorCode;
}

std::string Tree::printNodes() {
	if (this->root == nullptr) {
		return MSG_TREE_EMPTY;
	}
	else {
		return this->root->printNodes();
	}
}
void Tree::addVariable(std::string variable) {
	if (std::find(variables.begin(), variables.end(), variable) == variables.end()) {
		variables.push_back(variable);
	}
}
std::string Tree::vars() {
	std::string result;
	if (this->root == nullptr) {
		return MSG_TREE_EMPTY;
	}
	else if (this->variables.size() == 0) {
		return MSG_NO_VARIABLES;
	}
	else {
		int numberOfVariables = variables.size();
		std::string result = MSG_VARIABLES;
		for (auto iterator = variables.begin(); iterator != variables.end(); ++iterator) {
			result.append(*iterator);
			if (iterator + 1 != variables.end()) {
				result.append(COMMA_STRING);
				result.append(SPACE_STRING);
			}
		}
		return result;
	}
}

double Tree::computeValue(std::vector<int> *environment) {
	if (environment->size() != this->variables.size()) {
		//fail
	}
	if (this->root == nullptr) { //TODO: RETHINK OR REFACTOR
		return 0;
	}
	else {
		this->environment = environment;
		return this->root->computeValue();
	}
	
}

int Tree::indexOfVariable(std::string &variableName) {
	bool found = false;
	int index = 0;
	for (auto iterator = variables.begin(); iterator != variables.end() && !found;) {
		if (*iterator == variableName) {
			found = true;
		}
		else {
			++iterator;
			++index;
		}
	}
	return index;
}

int Tree::valueOfVariable(std::string &variableName) {
	return this->environment->at(indexOfVariable(variableName));
}
