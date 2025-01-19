#pragma once

#include "prime_defines.h"

PRIME_API void*
prime_MemAlloc(u64 size);

PRIME_API void
prime_MemFree(void* memory, u64 size);

PRIME_API void
prime_MemSet(void* memory, i32 value, u64 size);

PRIME_API void
prime_MemZero(void* memory, u64 size);

PRIME_API void
prime_MemCopy(void* memory_dest, const void* memory_src, u64 size);

PRIME_API void
prime_MemCopy(void* memory_dest, const void* memory_src, u64 size);
