#pragma once

#include "pr_defines.h"

#define PR_KILOBYTE 1024
#define PR_MEGABYTE 1024 * 1024
#define PR_GIGABYTE 1024 * 1024 * 1024
#define PR_MEMORY_MAX 10 * PR_MEGABYTE

struct PrAllocator;

PR_API PrAllocator*
prAllocatorCreate(u64 size);

PR_API void
prAllocatorDestroy(PrAllocator* allocator);

PR_API void*
prAllocatorAlloc(PrAllocator* allocator, u64 size);

PR_API void
prAllocatorClear(PrAllocator* allocator);
