
#pragma once

#include "prime/defines.h"

namespace prime::utils {

    i32 multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);

    i32 wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

    void consoleWrite(LogLevel level, const char* msg);

} // namespace prime::utils
    