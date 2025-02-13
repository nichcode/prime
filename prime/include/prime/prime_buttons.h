
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
primeButtonMapNames();

PAPI const char*
primeButtonGetName(u16 button);
