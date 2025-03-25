
#pragma once

#include "defines.h"
#include <stdarg.h>

PRIME_API char* primeFormat(const char* fmt, ...);
PRIME_API char* primeFormatArgs(const char* fmt, va_list args_list);

PRIME_API char* primeToString(const wchar_t* wstring);
PRIME_API wchar_t* primeToWstring(const char* string);

PRIME_API void primeWstringFree(wchar_t* wstring);
PRIME_API void primeStringFree(char* string);

PRIME_API const char* primeGetKeyName(u32 key);
PRIME_API const char* primeGetButtonName(u32 button);
PRIME_API const char* primeGetActionName(u32 action);
