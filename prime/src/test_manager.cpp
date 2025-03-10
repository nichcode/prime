
#include "prime/core/test_manager.h"
#include <vector>

namespace prime::core {

    struct Entry
    {
        TestFunc func = nullptr;
        const char* name = nullptr;
    };

    static std::vector<Entry> s_Tests;

    i32 TestManager::addTest(TestFunc func, const char *name)
    {
        Entry test;
        test.func = func;
        test.name = name;
        s_Tests.push_back(test);
        return 1;
    }

    void TestManager::run()
    {
        for (auto& test : s_Tests) {
            b8 result = test.func();
        }
    }

} // namespace prime