#include "Node.h"

Node::Node() {
	this->nodeType = NodeType::Undefined;
}

Node::Node(Tree *parentTree) {
	this->parentTree = parentTree;
}

int Node::parseString(std::string &stringToParse, int startIndex) {
	int stringLength = stringToParse.length();
	std::string expression;
	int currentIndex = startIndex;
	if (currentIndex >= stringLength) {
		this->nodeType = NodeType::Constant;
		this->constantValue = DEFAULT_CONSTANT;
		return currentIndex + 2;
	}
	else {
		while (currentIndex < stringLength && stringToParse.at(currentIndex) != SPACE) {
			currentIndex++;
		}
		currentIndex--;
		expression = stringToParse.substr(startIndex, currentIndex - startIndex + 1);
		int numberOfChildren;

		if (expression == OPERATION_SUM) {
			numberOfChildren = 2;
			this->nodeType = NodeType::OperationSum;
		}
		else if (expression == OPERATION_SUB) {
			numberOfChildren = 2;
			this->nodeType = NodeType::OperationSub;
		}
		else if (expression == OPERATION_MULT) {
			numberOfChildren = 2;
			this->nodeType = NodeType::OperationMult;
		}
		else if (expression == OPERATION_DIV) {
			numberOfChildren = 2;
			this->nodeType = NodeType::OperationDiv;
		}
		else if (expression == OPERATION_SIN) {
			numberOfChildren = 1;
			this->nodeType = NodeType::OperationSin;
		}
		else if (expression == OPERATION_COS) {
			numberOfChildren = 1;
			this->nodeType = NodeType::OperationCos;
		}
		else if (stringOps::isNumber(expression)) {
			numberOfChildren = 0;
			this->nodeType = NodeType::Constant;
			this->constantValue = std::atoi(expression.c_str());
		}
		else if (expression.length() == 0) {
			numberOfChildren = 0;
			this->nodeType = NodeType::Constant;
			this->constantValue = DEFAULT_CONSTANT;
		}
		else {
			numberOfChildren = 0;
			this->nodeType = NodeType::Variable;
			this->variableName = expression;
		}

		Node *child;
		switch (numberOfChildren) {
		case 0:
			return currentIndex + 2;
			break;
		case 1:
			child = new Node();
			children.push_back(child);
			return child->parseString(stringToParse, currentIndex + 2);
			break;
		case 2:
			child = new Node(this->parentTree);
			Node *secondChild = new Node(this->parentTree);
			children.push_back(child);
			children.push_back(secondChild);
			return secondChild->parseString(stringToParse, child->parseString(stringToParse, currentIndex + 2));
			break;
		}
	}
	
}
std::string Node::printNodes() {
	std::string result;
	switch (nodeType) {
	case Variable:
		result = variableName;
		break;
	case Constant:
		result = std::to_string(this->constantValue);
		break;
	case OperationCos:
		result = "cos (" + children.at(0)->printNodes() + ")";
		break;
	case OperationSin:
		result = "sin (" + children.at(0)->printNodes() + ")";
		break;
	case OperationSum:
		result = "(" + children.at(0)->printNodes() + " + " + children.at(1)->printNodes() + ")";
		break;
	case OperationSub:
		result = "(" + children.at(0)->printNodes() + " - " + children.at(1)->printNodes() + ")";
		break;
	case OperationMult:
		result = "(" + children.at(0)->printNodes() + " * " + children.at(1)->printNodes() + ")";
		break;
	case OperationDiv:
		result = "(" + children.at(0)->printNodes() + " / " + children.at(1)->printNodes() + ")";
		break;
	}
	return result;
}