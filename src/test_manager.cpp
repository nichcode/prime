
#include "prime/test_manager.h"
#include "prime/logger.h"

#include <vector>
#include "format"

namespace prime {

	struct TestEntry
	{
		str name;
		TestFunc function;
		TestEntry() : name(""), function(nullptr) {}
	};

	static std::vector<TestEntry> s_tests;

	void TestManager::add_test(TestFunc test_func, const str& name)
	{
		TestEntry entry;
		entry.function = test_func;
		entry.name = name;
		s_tests.push_back(entry);
	}

	void TestManager::run()
	{
		u32 passed = 0;
		u32 failed = 0;

		for (auto& test : s_tests) {
			b8 result = test.function();

			if (result) {
				str msg = std::format("[SUCCESS]: {}", test.name);
				PINFO(msg);
				++passed;
			}

			else {
				str msg = std::format("[FAILED]: {}", test.name);
				PINFO(msg);
				++failed;
			}
		}

		str msg = std::format("Results: {} passed, {} failed", passed, failed);
		PINFO(msg);;
		s_tests.clear();
	}
}