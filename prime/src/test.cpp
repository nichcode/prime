
#include "pch.h"

struct Entry
{
    prime_test_func func = nullptr;
    const char* name = nullptr;
};

static std::vector<Entry> s_Tests;
static void* s_TestsData = nullptr;

void prime_set_tests_data(void* user_data)
{
    s_TestsData = user_data;
}

i32 prime_add_test(prime_test_func func, const char* name)
{
    Entry test;
    test.func = func;
    test.name = name;
    s_Tests.push_back(test);
    return PRIME_PASSED;
}

void prime_run_tests()
{
    for (auto& test : s_Tests) {
        b8 result = test.func(s_TestsData);
    }
}