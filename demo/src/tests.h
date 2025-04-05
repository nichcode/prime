
#pragma once

#include "prime/prime.h"
#include <vector>

using TestFunc = b8(*)();

void addTest(TestFunc func, const char* name);
void runTests();

// tests
b8 windowTest();
b8 contextTest();
b8 renderTest();