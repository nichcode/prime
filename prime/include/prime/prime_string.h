#pragma once

#include "prime_defines.h"

struct prime_String;
struct prime_WString;

PRIME_API prime_String*
prime_CstrToString(const char* string);

PRIME_API prime_String*
prime_CopyString(const prime_String* string);

PRIME_API prime_String*
primeWStringToString(const prime_WString* wide_string);

PRIME_API void
prime_DestroyString(prime_String* string);

PRIME_API const char*
prime_GetCstr(const prime_String* string);

PRIME_API u64
prime_GetStringLength(const prime_String* string);

PRIME_API prime_String*
prime_FormatString(const char* fmt, ...);

PRIME_API prime_String*
prime_FormatStringWithArgs(const char* fmt, char* va_listp);

PRIME_API prime_WString*
prime_CopyWString(const prime_WString* wide_string);

PRIME_API prime_WString*
prime_WstrToWString(const wchar_t* wide_string);

PRIME_API prime_WString*
prime_StringToWString(const prime_String* string);

PRIME_API prime_WString*
prime_CstrToWString(const char* string);

PRIME_API void
prime_DestroyWString(prime_WString* wide_string);

PRIME_API const wchar_t*
prime_GetWstr(const prime_WString* wide_string);

PRIME_API u64
prime_GetWStringLength(const prime_WString* wide_string);