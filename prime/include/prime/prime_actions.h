
#pragma once

#include "prime_defines.h"

enum primeAction
{
	primeActionRelease,
	primeActionPress,
	primeActionRepeat,

	primeActionMax
};

PAPI void
prime_ActionMapNames();

PAPI const char*
prime_ActionGetName(u8 action);