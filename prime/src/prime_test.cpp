
#include "prime/prime_test.h"

#include <vector>

struct TestEntry
{
    const char* name = nullptr;
    primeTestFunc func = nullptr;
};

static std::vector<TestEntry> s_Tests;

u8
primeAddTest(const char* name, primeTestFunc func)
{
	TestEntry test;
	test.func = func;
	test.name = name;
	s_Tests.push_back(test);
    return 1;
}

void 
primeRunTests()
{
	u32 passed = 0;
	u32 failed = 0;

	for (auto& test : s_Tests) {
		b8 result = test.func();
	}
	s_Tests.clear();
}