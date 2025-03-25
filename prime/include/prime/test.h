
#pragma once

#include "defines.h"
#include "API.h"

PRIME_API void primeSetTestsData(void* data);
PRIME_API i32 primeAddTest(primeTestFunc func, const char* name);
PRIME_API void primeRunTests();