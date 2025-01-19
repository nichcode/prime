#pragma once

#include "prime/prime_log.h"
#include "prime/prime_device.h"

struct prime_Window;
struct prime_String;
struct prime_Window;
struct prime_Context;
struct prime_ContextHandle;

#ifdef PRIME_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

#endif // PR_PLATFORM_WINDOWS

void
prime_SetWindowContextHandle(prime_Window* window, prime_ContextHandle* context_handle);

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

prime_DeviceType
prime_GetDeviceType(prime_Device* device);

void
prime_AddContext(prime_Device* device, prime_Context* context);

void
prime_RemoveContext(prime_Device* device, prime_Context* context);