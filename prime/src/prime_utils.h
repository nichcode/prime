#pragma once

#include "prime/prime_defines.h"

#ifdef PRIME_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif // PR_PLATFORM_WINDOWS

void
windowSetContextHandle(prime_Window* window, prime_Context* context);

b8
windowHasContextHandle(prime_Window* window);

void
consoleWrite(const prime_String* message, prime_LogLevel level);

i32
multiByteToWideChar(
    const char* string,
    u32 string_len,
    wchar_t* wide_string);

i32
wideCharToMultiByte(
    const wchar_t* wide_string,
    u32 wide_string_len,
    char* string);

void
appendContext(prime_Device* device, prime_Context* context);

void
popContext(prime_Device* device, prime_Context* context);

void
appendVertexbuffer(prime_Device* device, prime_Vertexbuffer* vertexbuffer);

void
popVertexbuffer(prime_Device* device, prime_Vertexbuffer* vertexbuffer);

void
appendIndexbuffer(prime_Device* device, prime_Indexbuffer* indexbuffer);

void
popIndexbuffer(prime_Device* device, prime_Indexbuffer* indexbuffer);