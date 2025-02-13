
#include "prime/prime_test.h"

#include <vector>

struct TestEntry
{
    const char* name = nullptr;
    prime_TestFunc func = nullptr;
};

static std::vector<TestEntry> s_Tests;

u8
prime_AddTest(const char* name, prime_TestFunc func)
{
	TestEntry test;
	test.func = func;
	test.name = name;
	s_Tests.push_back(test);
    return 1;
}

void 
prime_RunTests()
{
	u32 passed = 0;
	u32 failed = 0;

	for (auto& test : s_Tests) {
		b8 result = test.func();
	}
	s_Tests.clear();
}