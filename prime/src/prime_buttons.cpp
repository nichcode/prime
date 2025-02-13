
#include "prime/prime_buttons.h"
#include "prime/prime_log.h"

#include <string>

static std::string s_ButtonNames[primeButtonMax + 1] = {};

void
primeButtonMapNames()
{
	s_ButtonNames[primeButtonLeft] = "Button Left";
	s_ButtonNames[primeButtonRight] = "Button Right";
	s_ButtonNames[primeButtonMiddle] = "Button Middle";
}

const char*
primeButtonGetName(u16 button)
{
	PASSERT_MSG(button >= 0, "Invalid button");
	PASSERT_MSG(button < primeButtonMax, "Invalid button");
	return s_ButtonNames[button].c_str();
}