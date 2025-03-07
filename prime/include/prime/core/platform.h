
#pragma once

#include "prime/defines.h"

namespace prime::core {

    class Platform
    {
    public:
        static i32 init();
        static void shutdown();
    };
    
} // namespace prime::core
