
#include "prime/prime_test.h"
#include "prime/prime_logger.h"

#include <vector>
#include "format"

namespace prime {

	struct TestEntry
	{
		str Name;
		TestFunc Function;
		TestEntry() : Name(""), Function(nullptr) {}
	};

	static std::vector<TestEntry> s_Tests;

	void TestManager::AddTest(TestFunc testFunc, const str& name)
	{
		TestEntry entry;
		entry.Function = testFunc;
		entry.Name = name;
		s_Tests.push_back(entry);
	}

	void TestManager::Run()
	{
		u32 passed = 0;
		u32 failed = 0;

		for (auto& test : s_Tests) {
			b8 result = test.Function();

			if (result) {
				str msg = std::format("[SUCCESS]: {}", test.Name);
				PINFO(msg);
				++passed;
			}

			else {
				str msg = std::format("[FAILED]: {}", test.Name);
				PINFO(msg);
				++failed;
			}
		}

		str msg = std::format("Results: {} passed, {} failed", passed, failed);
		PINFO(msg);;
		s_Tests.clear();
	}
}