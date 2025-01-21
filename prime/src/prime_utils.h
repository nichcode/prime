#pragma once

#include "prime/prime_defines.h"

#ifdef PRIME_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif // PR_PLATFORM_WINDOWS

void
prime_WindowSetContextHandle(prime_Window* window, prime_Context* context);

b8
prime_WindowHasContextHandle(prime_Window* window);

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

void
prime_AppendContext(prime_Device* device, prime_Context* context);

void
prime_PopContext(prime_Device* device, prime_Context* context);

void
prime_AppendVertexbuffer(prime_Device* device, prime_Vertexbuffer* vertexbuffer);

void
prime_PopVertexbuffer(prime_Device* device, prime_Vertexbuffer* vertexbuffer);

void
prime_AppendIndexbuffer(prime_Device* device, prime_Indexbuffer* indexbuffer);

void
prime_PopIndexbuffer(prime_Device* device, prime_Indexbuffer* indexbuffer);

void
prime_AppendShader(prime_Device* device, prime_Shader* shader);

void
prime_PopShader(prime_Device* device, prime_Shader* shader);