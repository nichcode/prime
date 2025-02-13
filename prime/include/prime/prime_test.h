
#pragma once

#include "prime/prime_defines.h"

using primeTestFunc = b8(*)();

PAPI u8
primeAddTest(const char* name, primeTestFunc func);

PAPI void 
primeRunTests();