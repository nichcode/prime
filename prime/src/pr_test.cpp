
#include "prime/pr_test.h"
#include "prime/pr_string.h"

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

		if (result) {
			PrString* msg = prStringFormat("[SUCCESS]: %s", test.name);
			prStringLog(msg);
			prStringDestroy(msg);
			++passed;
		}

		else {
			PrString* msg = prStringFormat("[FAILED]: %s", test.name);
			prStringLog(msg);
			prStringDestroy(msg);
			++failed;
		}
	}
	PrString* msg = prStringFormat("Results: %i passed, %i failed", passed, failed);
	prStringLog(msg);
	prStringDestroy(msg);
	s_Tests.clear();
}
