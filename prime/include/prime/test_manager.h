
#pragma once

#include "defines.h"

namespace prime {

    using TestFunc = b8(*)();

    class TestManager
    {
    public:
        static i32 addTest(TestFunc func, const char* name);
        static void run();
    };
        
} // namespace prime
