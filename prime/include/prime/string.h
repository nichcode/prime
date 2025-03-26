
#pragma once

#include "input.h"
#include <stdarg.h>

PRIME_API char* primeFormat(const char* fmt, ...);
PRIME_API char* primeFormatArgs(const char* fmt, va_list args_list);

PRIME_API char* primeToString(const wchar_t* wstring);
PRIME_API wchar_t* primeToWstring(const char* string);

PRIME_API void primeWstringFree(wchar_t* wstring);
PRIME_API void primeStringFree(char* string);

PRIME_API const char* primeGetKeyName(primeKey key);
PRIME_API const char* primeGetButtonName(primeButton button);
PRIME_API const char* primeGetActionName(primeAction action);
