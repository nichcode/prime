
#include "prime_win32platform.h"
#include "prime/prime_log.h"

#ifdef PRIME_PLATFORM_WINDOWS

#include "prime_wglcontext.h"

#include <memory>
#include <string>

#include "prime_utils.h"
#include "prime/prime_string.h"

static b8 s_WGLInit = false;

b8
prime_Init()
{
	s_Instance = GetModuleHandleW(nullptr);

	WNDCLASSEXW wc = {};
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.cbWndExtra = 0;
	wc.hbrBackground = NULL;
	wc.hCursor = LoadCursor(s_Instance, IDC_ARROW);
	wc.hIcon = LoadIcon(s_Instance, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(s_Instance, IDI_APPLICATION);
	wc.hInstance = s_Instance;
	wc.lpfnWndProc = prime_WinProc;
	wc.lpszClassName = s_ClassName;
	wc.lpszMenuName = NULL;
	wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	ATOM success = RegisterClassEx(&wc);
	PRIME_ASSERT_MSG(success, "Window Registration Failed");

	QueryPerformanceFrequency((LARGE_INTEGER*)&s_ClockFrequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&s_StartTime);

	s_TotalAllocated = 0;
	if (!s_WGLInit) {
		prime_WGLContextCreateDummy();
		s_WGLInit = true;
	}

	return PRIME_PASSED;
}

void
prime_Shutdown()
{
	UnregisterClassW(s_ClassName, s_Instance);
	s_TotalAllocated = 0;
}

void*
prime_MemAlloc(u64 size)
{
	s_TotalAllocated += size;
	return (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

void
prime_MemFree(void* memory, u64 size)
{
	if (memory) {
		s_TotalAllocated -= size;
		HeapFree(GetProcessHeap(), 0, memory);
		memory = nullptr;
	}
}

void
prime_MemSet(void* memory, i32 value, u64 size)
{
	if (memory) {
		memset(memory, value, size);
	}
}

void
prime_MemZero(void* memory, u64 size)
{
	if (memory) {
		memset(memory, 0, size);
	}
}

void
prime_MemCopy(void* memory_dest, const void* memory_src, u64 size)
{
	if (memory_dest && memory_src) {
		memcpy(memory_dest, memory_src, size);
	}
}

void
prime_ConsoleWrite(const prime_String* message, prime_LogLevel level)
{
	b8 error = level > prime_LogLevelWarn;
	HANDLE console = NULL;
	static u8 levels[5] = { 8, 2, 6, 4, 64 };

	if (error) {
		console = GetStdHandle(STD_ERROR_HANDLE);
	}
	else {
		console = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleTextAttribute(console, levels[level]);

	prime_WString* wide_str = prime_StringToWString(message);
	DWORD number_written = 0;

	WriteConsoleW(console,
		prime_GetWstr(wide_str),
		(DWORD)prime_GetWStringLength(wide_str),
		&number_written, 0);

	prime_DestroyWString(wide_str);
	SetConsoleTextAttribute(console, 15);
}

f32
prime_GetTime()
{
	u64 time;
	QueryPerformanceCounter((LARGE_INTEGER*)&time);
	return (f32)(time - s_StartTime) / s_ClockFrequency;
}

void
prime_Sleep(f64 milli_secs)
{
	Sleep((DWORD)milli_secs);
}

i32
prime_MultiByteToWideChar(
	const char* string,
	u32 string_len,
	wchar_t* wide_string)
{
	return MultiByteToWideChar(CP_UTF8, 0, string, -1, wide_string, string_len);
}

i32
prime_WideCharToMultiByte(
	const wchar_t* wide_string,
	u32 wide_string_len,
	char* string)
{
	return WideCharToMultiByte(CP_UTF8, 0, wide_string, -1, string, wide_string_len, 0, 0);
}

#endif // PRIME_PLATFORM_WINDOWS
