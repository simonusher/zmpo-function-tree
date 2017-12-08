#include <vld.h>
#include <iostream>
#include "TreeManager.h"
void main() {
	std::string expression = "cos + &@#a b";
	std::string expression2 = "* cos * a c d";
	TreeManager tm;
	std::cout << tm.printTree();
	std::cout << END_LINE;
	tm.createNewTree(expression);
	std::cout << tm.printTree();
	std::cout << END_LINE;
	std::cout << tm.getVars();
	std::cout << END_LINE;
	tm.joinNewTree(expression2);
	std::cout << tm.printTree();
	std::cout << END_LINE;
	std::cout << tm.getVars();
	double result;
	std::vector<int> environment;
	environment.push_back(10);
	environment.push_back(5);
	environment.push_back(6);
	std::cout << tm.computeValue(environment, result);
	std::cout << END_LINE;

	int i;
	std::cin >> i;
}