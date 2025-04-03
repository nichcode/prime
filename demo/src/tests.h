
#pragma once

#include "prime/prime.h"
#include <vector>

using TestFunc = b8(*)();

void addTest(TestFunc func);
void runTests();

// tests
b8 windowTest();