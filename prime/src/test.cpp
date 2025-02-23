
#include "prime/test.h"

#include <vector>

namespace prime {

    struct TestEntry
    {
        str name = "";
        TestFunc func = nullptr;
    };

    static std::vector<TestEntry> s_Tests;

    void TestManager::add(const str& name, TestFunc func)
    {
        TestEntry test;
        test.func = func;
        test.name = name;
        s_Tests.push_back(test);
    }

    void TestManager::run()
    {
        u32 passed = 0;
        u32 failed = 0;

        for (auto& test : s_Tests) {
            b8 result = test.func();
        }
        s_Tests.clear();        
    }

} // namespace prime
