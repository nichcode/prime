
#pragma once

#include <stdarg.h>

#include "prime_defines.h"

PAPI char*
primeStringDuplicate(const char* string);

PAPI void
primeStringCopy(char* dest_string, const char* src_string);

PAPI void
primeStringNcopy(char* dest_string, const char* src_string, u64 length);

PAPI void
primeStringFree(char* string);

PAPI u64
primeStringGetLength(const char* string);

PAPI char*
primeStringAdd(const char* string1, const char* string2);

PAPI char*
primeStringFormat(const char* fmt, ...);

PAPI char*
primeStringFormatArgs(const char* fmt, va_list args_list);

PAPI b8
primeStringEqual(const char* string1, const char* string2, b8 case_sensitive);

PAPI b8
primeStringEmpty(const char* string);

PAPI void
primeStringClear(char* string);

PAPI i32
primeStringGetIndex(const char* string1, const char* string2);

PAPI void
primeStringInsert(char* dest_string, const char* src_string, u32 pos, const char* string);

PAPI char*
primeStringInsertAlloc(const char* src_string, u32 pos, const char* string);

PAPI void
primeStringAssign(char* string, u32 pos, char c);

PAPI void
primeStringRemove(char* dest_string, const char* src_string, u32 pos, u32 length);

PAPI char*
primeF32ToString(f32 num);

PAPI char*
primeF64ToString(f64 num);

PAPI char*
primeU8ToString(u8 num);

PAPI char*
primeU16ToString(u16 num);

PAPI char*
primeU32ToString(u32 num);

PAPI char*
primeU64ToString(u64 num);

PAPI char*
primeI8ToString(i8 num);

PAPI char*
primeI16ToString(i16 num);

PAPI char*
primeI32ToString(i32 num);

PAPI char*
primeI64ToString(i64 num);

PAPI char*
primeB8ToString(b8 num);

PAPI wchar_t*
primeStringToWstring(const char* string);

PAPI char*
primeWstringToString(const wchar_t* wstring);

PAPI void
primeWstringFree(wchar_t* wstring);