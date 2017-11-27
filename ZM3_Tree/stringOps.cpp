#include "stringOps.h"

bool stringOps::isNumber(const std::string &string) {
	return string.find_first_not_of("0123456789") == std::string::npos;
}

std::string stringOps::removeLeadingZeros(const std::string &oldString) {
	int firstNotZeroIndex = oldString.find_first_not_of("0");
	if (firstNotZeroIndex == std::string::npos) {
		return EMPTY_STRING;
	}
	else {
		return oldString.substr(firstNotZeroIndex, oldString.length() - firstNotZeroIndex);
	}
}