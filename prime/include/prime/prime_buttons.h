
#pragma once

#include "prime_defines.h"

enum primeButton
{
	primeButtonLeft,
	primeButtonRight,
	primeButtonMiddle,

	primeButtonMax
};


PAPI void
prime_ButtonMapNames();

PAPI const char*
prime_ButtonGetName(u16 button);
