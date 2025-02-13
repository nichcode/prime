
#pragma once

#include "prime_defines.h"

PAPI void*
prime_MemoryAlloc(u64 size);

PAPI void
prime_MemoryFree(void* memory, u64 size);

PAPI void
prime_MemorySet(void* memory, i32 value, u64 size);

PAPI void
prime_MemoryZero(void* memory, u64 size);

PAPI void
prime_MemoryCopy(void* dest_memory, void* src_memory, u64 size);