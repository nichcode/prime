
#include "prime/prime.h"

#ifdef PR_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // !WIN32_LEAN_AND_MEAN

#include "pr_platform.h"
#include <memory>

static u64 s_TotalAllocated = 0;

b8
prInit()
{
	s_TotalAllocated = 0;
	PR_INFO("Prime Initialized!");
	return PR_PASSED;
}

void
prShutdown()
{
	s_TotalAllocated = 0;
	PR_INFO("Prime Shutdown!");
}

void*
prMemAlloc(u64 size)
{
	s_TotalAllocated += size;
	void* block = malloc(size);
	if (block) {
		memset(block, 0, size);
	}
	return block;
}

void
prMemFree(void* memory, u64 size)
{
	if (memory) {
		s_TotalAllocated -= size;
		free(memory);
	}
}

void
prMemSet(void* memory, i32 value, u64 size)
{
	if (memory) {
		memset(memory, value, size);
	}
}

void
prMemZero(void* memory, u64 size)
{
	if (memory) {
		memset(memory, 0, size);
	}
}

void
prMemCopy(void* memory_dest, const void* memory_src, u64 size)
{
	if (memory_dest && memory_src) {
		memcpy(memory_dest, memory_src, size);
	}
}

void
prPlatformConsoleWrite(const char* message, PrLogLevel level)
{
	b8 error = level > PrLogLevelWarn;
	HANDLE console = NULL;
	static u8 levels[5] = { 8, 2, 6, 4, 64 };

	if (error) {
		console = GetStdHandle(STD_ERROR_HANDLE);
	}
	else {
		console = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleTextAttribute(console, levels[level]);
	u64 length = strlen(message);
	LPDWORD number_written = 0;
	WriteConsoleA(console, message, (DWORD)length, number_written, 0);
	SetConsoleTextAttribute(console, 15);
}

#endif // PR_PLATFORM_WINDOWS
