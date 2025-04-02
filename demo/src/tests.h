
#pragma once

#include "prime/prime.h"

using TestFunc = b8(*)();

void addTest(TestFunc func, const char* name);
void runTests();