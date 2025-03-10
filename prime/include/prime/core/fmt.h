
#pragma once

#include "prime/defines.h"

namespace prime::core {

    str toString(const wchar_t* wstring);
    str toString(const wstr& wstring);

    wstr toWideString(const char* string);
    wstr toWideString(const str& string);

    str format(const char* fmt, ...);
    
} // namespace prime::core
