
#pragma once

#include "defines.h"

namespace prime {

    class Utils
    {
    private:
        static char*
        format(const char* fmt, va_list args_list);

    public:
        static str 
        format(const char* fmt, ...);
    };
    
} // namespace prime