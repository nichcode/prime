#pragma once

#include "pr_string.h"

PR_API void*
prMemAlloc(u64 size);

PR_API void
prMemFree(void* memory, u64 size);

PR_API void
prMemSet(void* memory, i32 value, u64 size);

PR_API void
prMemZero(void* memory, u64 size);

PR_API void
prMemCopy(void* memory_dest, const void* memory_src, u64 size);

PR_API void
prMemCopy(void* memory_dest, const void* memory_src, u64 size);
