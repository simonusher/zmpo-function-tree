#include "Node.h"
#include <iostream>
void main() {
	Tree *t = new Tree();
	Tree *t2 = new Tree();
	std::string expression = "cos + a b";
	t->parseExpression(expression);
	t2 = t;
	std::cout << t->printNodes();
	std::cout << END_LINE;
	std::cout << t2->printNodes();
	std::cout << END_LINE;
	std::cout << t->vars();
	std::cout << END_LINE;
	std::cout << t2->vars();
	std::vector<int> env;
	env.push_back(10);
	env.push_back(5);
	std::cout << END_LINE;
	std::cout << t->computeValue(&env);
	int i;
	std::cin >> i;
}