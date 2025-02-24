
#pragma once

#include "defines.h"

#include <stdarg.h>

namespace prime {

    class Utils
    {
    private:
        static char*
        formatArgs(const char* fmt, va_list args_list);

    public:
        static void
        init();

        static str 
        format(const char* fmt, ...);

        static const char* 
        getName(Action action);

        static const char* 
        getName(Button button);

        static const char* 
        getName(Key key);

        static str 
        toString(const wstr& wstring);

        static wstr 
        toWstring(const str& string);
    };
    
} // namespace prime