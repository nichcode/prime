
#pragma once

#include "defines.h"
#include <stdarg.h>

PRIME_API char* prime_string_format(const char* fmt, ...);
PRIME_API char* prime_string_format_args(const char* fmt, va_list args_list);

PRIME_API char* prime_wstring_tostring(const wchar_t* wstring);
PRIME_API wchar_t* prime_string_towstring(const char* string);

PRIME_API void prime_wstring_free(wchar_t* wstring);
PRIME_API void prime_string_free(char* string);
