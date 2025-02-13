
#pragma once

#include "prime_defines.h"

PAPI void*
primeMemoryAlloc(u64 size);

PAPI void
primeMemoryFree(void* memory, u64 size);

PAPI void
primeMemorySet(void* memory, i32 value, u64 size);

PAPI void
primeMemoryZero(void* memory, u64 size);

PAPI void
primeMemoryCopy(void* dest_memory, void* src_memory, u64 size);