
#pragma once

#include "defines.h"

namespace prime {

    using TestFunc = b8(*)();

    class TestManager
    {
    public:
        static void add(const str& name, TestFunc func);
        static void run();
    };
    
} // namespace prime




