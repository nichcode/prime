
#pragma once

#include "prime/prime_defines.h"
#include "prime/prime_log.h"

#ifdef PPLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#endif // PPLATFORM_WINDOWS

static primeAllocator* s_Allocator = nullptr;

i32
prime_MultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);

i32
prime_WcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

char*
prime_StringFormatSys(const char* fmt, ...);

void
prime_StringFreeSys(char* string);

void
prime_ConsoleWrite(primeLogLevel level, const char* out_msg);