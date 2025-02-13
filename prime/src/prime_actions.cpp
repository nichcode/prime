
#include "prime/prime_actions.h"
#include "prime/prime_log.h"

#include <string>

static std::string s_ActionNames[primeActionMax + 1] = {};

void
prime_ActionMapNames()
{
    s_ActionNames[primeActionRelease] = "Release";
	s_ActionNames[primeActionPress] = "Press";
	s_ActionNames[primeActionRepeat] = "Repeat";
}

const char*
prime_ActionGetName(u8 action)
{
	PASSERT_MSG(action >= 0, "Invalid action");
	PASSERT_MSG(action < primeActionMax, "Invalid action");
	return s_ActionNames[action].c_str();
}