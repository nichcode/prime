
#include "prime/prime_test.h"

#include <vector>

// TODO: remove
#include <iostream>

namespace prime {

	struct TestEntry
	{
		str Name;
		TestFunc Function;
		TestEntry() : Name(""), Function(nullptr) {}
	};

	static std::vector<TestEntry> s_Tests;

	void TestManager::Init()
	{

	}

	void TestManager::Shutdown()
	{
		s_Tests.clear();
	}

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

		for (auto test : s_Tests) {
			b8 result = test.Function();

			if (result) {
				// TODO: remove
				std::cout << "[SUCCESS]" << test.Name << std::endl;
				++passed;
			}

			else {
				std::cout << "[FAILED]" << test.Name << std::endl;
				++failed;
			}
		}

		std::cout << "Results: " << passed << "passed, " << failed << "failed" << std::endl;
	}
}