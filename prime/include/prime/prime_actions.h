
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
primeActionMapNames();

PAPI const char*
primeActionGetName(u8 action);