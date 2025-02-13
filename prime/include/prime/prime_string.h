
#pragma once

#include <stdarg.h>

#include "prime_defines.h"

PAPI char*
prime_StringDuplicate(const char* string);

PAPI void
prime_StringCopy(char* dest_string, const char* src_string);

PAPI void
prime_StringNcopy(char* dest_string, const char* src_string, u64 length);

PAPI void
prime_StringFree(char* string);

PAPI u64
prime_StringGetLength(const char* string);

PAPI char*
prime_StringAdd(const char* string1, const char* string2);

PAPI char*
prime_StringFormat(const char* fmt, ...);

PAPI char*
prime_StringFormatArgs(const char* fmt, va_list args_list);

PAPI b8
prime_StringEqual(const char* string1, const char* string2, b8 case_sensitive);

PAPI b8
prime_StringEmpty(const char* string);

PAPI void
prime_StringClear(char* string);

PAPI i32
prime_StringGetIndex(const char* string1, const char* string2);

PAPI void
prime_StringInsert(char* dest_string, const char* src_string, u32 pos, const char* string);

PAPI char*
prime_StringInsertAlloc(const char* src_string, u32 pos, const char* string);

PAPI void
prime_StringAssign(char* string, u32 pos, char c);

PAPI void
prime_StringRemove(char* dest_string, const char* src_string, u32 pos, u32 length);

PAPI char*
prime_F32ToString(f32 num);

PAPI char*
prime_F64ToString(f64 num);

PAPI char*
prime_U8ToString(u8 num);

PAPI char*
prime_U16ToString(u16 num);

PAPI char*
prime_U32ToString(u32 num);

PAPI char*
prime_U64ToString(u64 num);

PAPI char*
prime_I8ToString(i8 num);

PAPI char*
prime_I16ToString(i16 num);

PAPI char*
prime_I32ToString(i32 num);

PAPI char*
prime_I64ToString(i64 num);

PAPI char*
prime_B8ToString(b8 num);

PAPI wchar_t*
prime_StringToWstring(const char* string);

PAPI char*
prime_WstringToString(const wchar_t* wstring);

PAPI void
prime_WstringFree(wchar_t* wstring);