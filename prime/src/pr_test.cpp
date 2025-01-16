
#include "prime/pr_test.h"

#include <vector>

static std::vector<PrTestEntry> s_Tests;

void 
prTestsAdd(const PrTestEntry& test_entry)
{
	PrTestEntry test;
	test.function = test_entry.function;
	test.name = test_entry.name;
	s_Tests.push_back(test);
}

void 
prTestsRun()
{
	u32 passed = 0;
	u32 failed = 0;

	for (auto& test : s_Tests) {
		b8 result = test.function();

		// TODO:

		/*if (result) {
			PrimeString* msg = primeStringFormat("[SUCCESS]: %s", test.name);
			PRIME_INFO(msg->buffer);
			++passed;
		}

		else {
			PrimeString* msg = primeStringFormat("[FAILED]: %s", test.name);
			PRIME_INFO(msg->buffer);
			++failed;
		}*/
	}
	//PrimeString* msg = primeStringFormat("Results: %i passed, %i failed", passed, failed);
	//PRIME_INFO(msg->buffer);
	s_Tests.clear();
}
