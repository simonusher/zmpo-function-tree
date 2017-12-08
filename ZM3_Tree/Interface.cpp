#include "Interface.h"

Interface::Interface() {
	this->treeManager = new TreeManager();
	this->finished = false;
}

Interface::~Interface() {
	delete this->treeManager;
}

void Interface::run() {
	while (!finished) {
		printCommandPrompt();
		readCommand();
		splitCurrentCommand();
		selectAndPerformOperation();
		printProgramResponse();
	}
	std::cin.get();
}

void Interface::readCommand() {
	std::getline(std::cin, this->currentCommand);
}

void Interface::splitCurrentCommand() {
	removeLeadingSpaces(currentCommand);
	int spaceIndex = currentCommand.find_first_of(SPACE);
	if (spaceIndex != currentCommand.npos) {
		currentCommandArguments = currentCommand.substr(spaceIndex + 1, currentCommand.length() - spaceIndex + 1);
		currentCommand.erase(spaceIndex, currentCommand.length() - spaceIndex);
	}
}

void Interface::selectAndPerformOperation() {
	if(currentCommand.length() != 0){
		if (currentCommand == COMMAND_ENTER) {
			processCommandEnter();
		}
		else if (currentCommand == COMMAND_VARS) {
			processCommandVars();
		}
		else if (currentCommand == COMMAND_PRINT) {
			processCommandPrint();
		}
		else if (currentCommand == COMMAND_COMP) {
			processCommandComp();
		}
		else if (currentCommand == COMMAND_JOIN) {
			processCommandJoin();
		}
		else if (currentCommand == COMMAND_EXIT) {
			this->finished = true;
			programResponse = PROMPT_EXIT;
		}
		else {
			programResponse = APOSTROPHE + currentCommand + APOSTROPHE + PROMPT_ERROR_INVALID_COMMAND;
		}
	}
	else {
		programResponse = EMPTY_STRING;
	}
	this->currentCommand = EMPTY_STRING;
	this->currentCommandArguments = EMPTY_STRING;
	this->argsSplit.clear();
}

void Interface::removeLeadingSpaces(std::string &string) {
	int firstNotSpaceIndex = string.find_first_not_of(SPACE);
	if (firstNotSpaceIndex == string.npos) {
		string.clear();
	}
	else {
		string.erase(0, firstNotSpaceIndex);
	}
}

void Interface::printProgramResponse() {
	if (this->programResponse != EMPTY_STRING) {
		std::cout << programResponse;
		if (!finished) {
			std::cout << std::endl;
		}
		this->programResponse = EMPTY_STRING;
	}
}

void Interface::printCommandPrompt() {
	std::cout << COMMAND_PROMPT + SPACE;
}

bool Interface::isArgumentNumber(std::string &argument) {
	return argument.find_first_not_of("0123456789") == argument.npos;
}

bool Interface::argumentOverflowsInt(std::string &argument) {
	//check string length for overflow
	if (argument.size() < MAX_INT_STRING_LENGTH) {
		return false;
	}
	if (argument.size() > MAX_INT_STRING_LENGTH) {
		return true;
	}
	else {
		bool overflows = false;
		std::string::const_iterator it = argument.begin();
		std::string::const_iterator maxIntIt = MAX_INT_STRING.begin();
		while (it != argument.end() && !overflows) {
			if ((*maxIntIt) < (*it)) {
				overflows = true;
			}
			++it;
			++maxIntIt;
		}
		return overflows;
	}
}

bool Interface::argumentsCorrect() {
	bool isCorrect = true;
	for (int i = 0; i < argsSplit.size() && isCorrect; i++) {
		if (!isArgumentNumber(argsSplit.at(i)) || argumentOverflowsInt(argsSplit.at(i))) {
			isCorrect = false;
		}
	}
	return isCorrect;
}

void Interface::processCommandEnter() {
	int errorCode = treeManager->createNewTree(currentCommandArguments);
	if (errorCode == SUCCESS) {
		programResponse = PROMPT_CREATED_NEW_TREE;
	}
	else {
		programResponse = PROMPT_ERROR_WHILE_PARSING_FORMULA + treeManager->printTree();
	}
}

void Interface::processCommandVars() {
	programResponse = treeManager->getVars();
}

void Interface::processCommandPrint() {
	programResponse = treeManager->printTree();
}

void Interface::processCommandComp() {
	std::istringstream iss(currentCommandArguments);
	std::copy(std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>(),
		std::back_inserter(argsSplit));
	if (argumentsCorrect()) {
		std::vector<int> numericArgs;
		for (int i = 0; i < argsSplit.size(); i++) {
			numericArgs.push_back(atoi(argsSplit.at(i).c_str()));
		}
		double result;
		int errorCode = treeManager->computeValue(numericArgs, result);
		switch (errorCode) {
		case ERROR_INCORRECT_NUMBER_OF_VARIABLES:
			programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND + APOSTROPHE + currentCommand + APOSTROPHE + FULL_STOP;
			break;
		case SUCCESS:
			programResponse = PROMPT_EVALUATED_EXPRESSION + std::to_string(result);
			break;
		case ERROR_TREE_NOT_CREATED:
			programResponse = PROMPT_ERROR_TREE_NOT_CREATED;
			break;
		}
	}
	else {
		programResponse = PROMPT_ERROR_INVALID_ARGUMENTS_FOR_COMMAND + APOSTROPHE + currentCommand + APOSTROPHE + FULL_STOP;
	}
}

void Interface::processCommandJoin() {
	int errorCode = treeManager->joinNewTree(currentCommandArguments);
	switch (errorCode) {
	case SUCCESS:
		programResponse = PROMPT_JOINED_NEW_TREE;
		break;
	case ERROR_TREE_NOT_CREATED:
		programResponse = PROMPT_ERROR_TREE_NOT_CREATED;
		break;
	default:
		programResponse = PROMPT_ERROR_WHILE_PARSING_FORMULA_FOR_NEW_TREE + treeManager->printTree();
	}
}
