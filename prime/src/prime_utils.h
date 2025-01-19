#pragma once

#include "prime/prime_defines.h"
#include "prime/prime_log.h"

struct prime_Window;
struct prime_String;
struct prime_Window;
struct prime_Context;

#ifdef PRIME_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif // PR_PLATFORM_WINDOWS

void
prime_SetWindowContext(prime_Window* window, prime_Context* context);

b8
prime_WindowHasContext(prime_Window* window);

void
prime_ConsoleWrite(const prime_String* message, prime_LogLevel level);

i32
prime_MultiByteToWideChar(
    const char* string,
    u32 string_len,
    wchar_t* wide_string);

i32
prime_WideCharToMultiByte(
    const wchar_t* wide_string,
    u32 wide_string_len,
    char* string);