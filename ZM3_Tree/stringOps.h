#pragma once
#include <string>
#include "constants.h"
namespace stringOps {
	bool isNumber(const std::string &string);

	std::string removeLeadingZeros(const std::string &oldString);
}