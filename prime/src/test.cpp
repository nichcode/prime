
#include "pch.h"

struct Entry
{
    primeTestFunc func = nullptr;
    const char* name = nullptr;
};

static std::vector<Entry> s_Tests;
static void* s_TestsData = nullptr;

void primeSetTestsData(void* data)
{
    s_TestsData = data;
}

i32 primeAddTest(primeTestFunc func, const char* name)
{
    Entry test;
    test.func = func;
    test.name = name;
    s_Tests.push_back(test);
    return PRIME_PASSED;
}

void primeRunTests()
{
    for (auto& test : s_Tests) {
        b8 result = test.func(s_TestsData);
    }
}