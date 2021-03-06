#pragma once
#include "TreeManager.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
//constants
//commands
//0 arguments
const std::string COMMAND_PRINT = "print";
const std::string COMMAND_VARS = "vars";
const std::string COMMAND_EXIT = "exit";
//variable number of arguments
const std::string COMMAND_ENTER = "enter";
const std::string COMMAND_COMP = "comp";
const std::string COMMAND_JOIN = "join";

//SUCCESS PROMPTS
const std::string PROMPT_CREATED_NEW_TREE = "Created new tree.";
const std::string PROMPT_JOINED_NEW_TREE = "Successfully joined new tree at old tree's leaf.";
const std::string PROMPT_EVALUATED_EXPRESSION = "Expression evaluated. Result: ";
const std::string PROMPT_EXIT = "Program finished by user. Press any key to exit.";

//error messages
const std::string PROMPT_ERROR_INVALID_COMMAND = " is not recognized as an internal command.";
const std::string PROMPT_ERROR_INVALID_ARGUMENTS_NUMBER_FOR_COMMAND = "Invalid number of arguments for command ";
const std::string PROMPT_ERROR_INVALID_ARGUMENTS_FOR_COMMAND = "Invalid arguments for command ";
const std::string PROMPT_ERROR_TREE_NOT_CREATED = "Tree not created yet!";
const std::string PROMPT_ERROR_WHILE_PARSING_FORMULA = "An error occured while parsing formula.\nUsing this formula instead: ";
const std::string PROMPT_ERROR_WHILE_PARSING_FORMULA_FOR_NEW_TREE = "An error occured while parsing formula for the second tree.\nThis is the new tree: ";
//utility strings
const std::string COMMAND_PROMPT = "$";
const std::string HELP_PROMPT = "Accepted commands: \nenter <formula> - creates new tree using <formula>\nvars - prints variables in current tree\nprint - prints current tree in RPN\ncomp <var0> <var1>...<varN> - computes current formula using provided environment\njoin <formula> - creates new tree using <formula> and attatches it to existing tree\n";

class Interface {
public:
	Interface();
	~Interface();
	void run();

private:
	TreeManager* treeManager;
	bool finished;
	std::string currentCommand;
	std::string currentCommandArguments;
	std::string programResponse;
	std::vector<std::string> argsSplit;
	void readCommand();
	void splitCurrentCommand();
	void selectAndPerformOperation();
	void removeLeadingSpaces(std::string &string);

	void printProgramResponse();
	void printCommandPrompt();
	bool argumentsCorrect();
	void processCommandEnter();
	void processCommandVars();
	void processCommandPrint();
	void processCommandComp();
	void processCommandJoin();
}
;