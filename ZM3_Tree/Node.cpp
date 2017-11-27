#include "Node.h"
Node::Node(Tree *parentTree) {
	this->nodeType = NodeType::Undefined;
	this->parentTree = parentTree;
}

Node::Node(Node &otherNode, Tree *parentTree) {
	this->parentTree = parentTree;
	int nodeType = otherNode.nodeType;
	if (nodeType == NodeType::Constant) {
		this->constantValue = otherNode.constantValue;
	}
	else if (nodeType == NodeType::Variable) {
		this->variableName = otherNode.variableName;
	}
	for (int i = 0; i < otherNode.children.size(); i++) {
		this->children.push_back(new Node(*(otherNode.children.at(i)), parentTree));
	}
}

Node::~Node() {
	for each (Node* childPtr in children) {
		delete childPtr;
	}
}

int Node::parseString(std::string &stringToParse, int startIndex) {

	int stringLength = stringToParse.length();
	//omitLeadingSpaces
	while (startIndex < stringLength && stringToParse.at(startIndex) == SPACE) {
		startIndex++;
	}

	std::string expression;
	
	if (startIndex >= stringLength) {
		this->nodeType = NodeType::Constant;
		this->constantValue = DEFAULT_CONSTANT;
		this->parentTree->errorCode = ERROR_WHILE_PARSING_STRING;
		return startIndex;
	}
	else {
		int currentIndex = startIndex;
		while (currentIndex < stringLength && stringToParse.at(currentIndex) != SPACE) {
			currentIndex++;
		}
		expression = stringToParse.substr(startIndex, currentIndex - startIndex);
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
			this->parentTree->addVariable(expression);
		}

		Node *child;
		switch (numberOfChildren) {
		case 0:
			return currentIndex;
			break;
		case 1:
			child = new Node(this->parentTree);
			children.push_back(child);
			return child->parseString(stringToParse, currentIndex);
			break;
		case 2:
			child = new Node(this->parentTree);
			Node *secondChild = new Node(this->parentTree);
			children.push_back(child);
			children.push_back(secondChild);
			return secondChild->parseString(stringToParse, child->parseString(stringToParse, currentIndex));
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

double Node::computeValue() {
	switch (this->nodeType) {
	case OperationSum:
		return this->children.at(0)->computeValue() + this->children.at(1)->computeValue();
		break;
	case OperationSub:
		return this->children.at(0)->computeValue() - this->children.at(1)->computeValue();
		break;
	case OperationMult:
		return this->children.at(0)->computeValue() * this->children.at(1)->computeValue();
		break;
	case OperationDiv:
		return this->children.at(0)->computeValue() / this->children.at(1)->computeValue();
		break;
	case OperationSin:
		return std::sin(this->children.at(0)->computeValue());
		break;
	case OperationCos:
		return std::cos(this->children.at(0)->computeValue());
		break;
	case Constant:
		return this->constantValue;
		break;
	case Variable:
		return this->parentTree->valueOfVariable(this->variableName);
		break;
	}
	return 0;
}
