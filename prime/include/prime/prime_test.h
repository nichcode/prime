#pragma once

#include "prime_defines.h"

using prime_TestFunc = b8(*)();

struct prime_TestEntry
{
	const char* name = nullptr;
	prime_TestFunc function = nullptr;
};

PRIME_API void
prime_TestManagerAddTest(prime_TestFunc function, const char* name);

PRIME_API void
prime_TestManagerRunTests();