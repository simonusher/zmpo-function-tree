#include "Node.h"
#include <iostream>
void main() {
	Node t;
	std::string xd = "+ + + - - - cos 321";
	t.parseString(xd, 0);
	std::cout << t.printNodes();
	int i;
	std::cin >> i;
}