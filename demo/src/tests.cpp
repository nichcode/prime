
#pragma once

#include "tests.h"
#include <vector>

struct Entry
{
    TestFunc func;
    const char* name;
};

static std::vector<Entry> s_Tests;

void addTest(TestFunc func, const char* name)
{
    Entry test;
    test.func = func;
    test.name = name;
    s_Tests.push_back(test);
}

void runTests()
{
    for (auto& test : s_Tests) {
        b8 result = test.func();
    }
}