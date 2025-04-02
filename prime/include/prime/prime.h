
#pragma once

#include "prime_defines.h"
#include <stdarg.h>

using prime_DeviceType = u32;

enum prime_DeviceTypes
{
    PRIME_DEVICE_OPENGL
};

// TODO: remove
#define PRIME_ASSERT_MSG(expr, ...)

struct prime_Allocator;

PRIME_API b8 prime_Init(prime_DeviceType type);
PRIME_API void prime_Shutdown();

PRIME_API prime_Allocator* prime_CreateAllocator(u64 size);
PRIME_API void prime_DestroyAllocator(prime_Allocator* allocator);

PRIME_API void* prime_Allocate(prime_Allocator* allocator, u64 size);
PRIME_API void prime_ClearAllocator(prime_Allocator* allocator);

PRIME_API char* prime_Format(const char* fmt, ...);
PRIME_API char* prime_FormatArgs(const char* fmt, va_list args_list);

PRIME_API char* prime_ToString(const wchar_t* wstring);
PRIME_API wchar_t* prime_ToWstring(const char* string);