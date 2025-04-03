
#pragma once

#include "tests.h"
#include <vector>

static std::vector<TestFunc> s_Tests;

void addTest(TestFunc func)
{
    s_Tests.push_back(func);
}

void runTests()
{
    for (TestFunc func : s_Tests) {
        b8 result = func();
    }
}