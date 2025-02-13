
#include "prime/prime_platform.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>

static u64 s_UsedMemory = 0;

// TODO: remove
#include <iostream>

u8
prime_PlatformInit()
{
    // TODO: remove
    std::cout << "Prime Win32Platform Init" << std::endl;
    return 1;
}

void
prime_PlatformShutdown()
{
    // TODO: remove
    std::cout << "Prime Win32Platform Shutdown" << std::endl;
}

void*
prime_MemoryAlloc(u64 size)
{
    s_UsedMemory += size;
	return (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

void
prime_MemoryFree(void* memory, u64 size)
{
    // TODO: Assertions
    s_UsedMemory -= size;
	HeapFree(GetProcessHeap(), 0, memory);
	memory = nullptr;
}

void
prime_MemorySet(void* memory, i32 value, u64 size)
{
    // Assertions
    memset(memory, value, size);
}

void
prime_MemoryZero(void* memory, u64 size)
{
    // Assertions
    memset(memory, 0, size);
}

void
prime_MemoryCopy(void* dest_memory, void* src_memory, u64 size)
{
    // TODO: Assertions
    memcpy(dest_memory, src_memory, size);
}