
#include "prime/prime_platform.h"
#include "prime_utils.h"
#include "prime/prime_memory.h"
#include "prime/prime_string.h"

static u64 s_UsedMemory = 0;

u8
prime_PlatformInit()
{
    PINFO("Prime Win32Platform Init");
    return 1;
}

void
prime_PlatformShutdown()
{
    PINFO("Prime Win32Platform Shutdown");
}

void*
prime_MemoryAlloc(u64 size)
{
    PASSERT_MSG(size, "size is invalid");
    s_UsedMemory += size;
	return (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

void
prime_MemoryFree(void* memory, u64 size)
{
    PASSERT_MSG(memory, "memory is null");
    s_UsedMemory -= size;
	HeapFree(GetProcessHeap(), 0, memory);
	memory = nullptr;
}

void
prime_MemorySet(void* memory, i32 value, u64 size)
{
    PASSERT_MSG(memory, "memory is null");
    memset(memory, value, size);
}

void
prime_MemoryZero(void* memory, u64 size)
{
    PASSERT_MSG(memory, "memory is null");
    memset(memory, 0, size);
}

void
prime_MemoryCopy(void* dest_memory, void* src_memory, u64 size)
{
    PASSERT_MSG(dest_memory, "dest_memory is null");
    PASSERT_MSG(src_memory, "src_memory is null");
    memcpy(dest_memory, src_memory, size);
}

i32
prime_MultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr)
{
    return MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, str_len);
}

i32
prime_WcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str)
{
    return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, wstr_len, 0, 0);
}

void
prime_ConsoleWrite(primeLogLevel level, const char* out_msg)
{
	b8 error = level > primeLogLevelWarn;
	HANDLE console = NULL;
	static u8 levels[5] = { 8, 2, 6, 4, 64 };

	if (error) {
		console = GetStdHandle(STD_ERROR_HANDLE);
	}
	else {
		console = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	SetConsoleTextAttribute(console, levels[level]);
	wchar_t* wstr = prime_StringToWstring(out_msg);
	DWORD number_written = 0;

	WriteConsoleW(console, wstr, (DWORD)wcslen(wstr), &number_written, 0);
	prime_WstringFree(wstr);
	SetConsoleTextAttribute(console, 15);
}