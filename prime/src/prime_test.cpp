
#include "prime/prime_test.h"
#include "prime/prime_string.h"
#include "prime/prime_log.h"

#include <vector>

static std::vector<prime_TestEntry> s_Tests;

void 
prime_AddTest(prime_TestFunc function, const char* name)
{
	prime_TestEntry test;
	test.function = function;
	test.name = name;
	s_Tests.push_back(test);
}

void 
prime_RunTests()
{
	u32 passed = 0;
	u32 failed = 0;

	for (auto& test : s_Tests) {
		b8 result = test.function();

		if (result) {
			prime_String* msg = prime_FormatString("[SUCCESS]: %s", test.name);
			prime_LogString(msg);
			prime_DestroyString(msg);
			++passed;
		}

		else {
			prime_String* msg = prime_FormatString("[FAILED]: %s", test.name);
			prime_LogString(msg);
			prime_DestroyString(msg);
			++failed;
		}
	}
	prime_String* msg = prime_FormatString("Results: %i passed, %i failed", passed, failed);
	prime_LogString(msg);
	prime_DestroyString(msg);
	s_Tests.clear();
}
