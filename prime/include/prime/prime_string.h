#pragma once

#include "prime_defines.h"

PRIME_API prime_String*
prime_StringFromCstr(const char* string);

PRIME_API prime_String*
prime_StringCopy(const prime_String* string);

PRIME_API prime_String*
prime_StringFromWString(const prime_WString* wide_string);

PRIME_API void
prime_StringDestroy(prime_String* string);

PRIME_API const char*
prime_StringGetCstr(const prime_String* string);

PRIME_API u64
prime_StringGetLength(const prime_String* string);

PRIME_API prime_String*
prime_StringFormat(const char* fmt, ...);

PRIME_API prime_String*
prime_StringFormatArgs(const char* fmt, char* va_listp);

PRIME_API prime_WString*
prime_WStringCopy(const prime_WString* wide_string);

PRIME_API prime_WString*
prime_WStringFromWstr(const wchar_t* wide_string);

PRIME_API prime_WString*
prime_WStringFromString(const prime_String* string);

PRIME_API prime_WString*
prime_WStringFromCstr(const char* string);

PRIME_API void
prime_WStringDestroy(prime_WString* wide_string);

PRIME_API const wchar_t*
prime_WStringGetWstr(const prime_WString* wide_string);

PRIME_API u64
prime_WStringGetLength(const prime_WString* wide_string);