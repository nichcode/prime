
#include "pr_win32platform.h"

#ifdef PR_PLATFORM_WINDOWS

#include "pr_wglcontext.h"

#include <memory>
#include <string>

#include "pr_platform.h"
#include "prime/pr_string.h"

static b8 s_WGLInit = false;

b8
prInit()
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
	wc.lpfnWndProc = prWinProc;
	wc.lpszClassName = s_ClassName;
	wc.lpszMenuName = NULL;
	wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	ATOM success = RegisterClassEx(&wc);
	PR_ASSERT_MSG(success, "Window Registration Failed");

	QueryPerformanceFrequency((LARGE_INTEGER*)&s_ClockFrequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&s_StartTime);

	s_TotalAllocated = 0;
	if (!s_WGLInit) {
		prWGLContextCreateDummy();
		s_WGLInit = true;
	}

	PR_INFO("Prime Initialized!");
	return PR_PASSED;
}

void
prShutdown()
{
	UnregisterClassW(s_ClassName, s_Instance);
	s_TotalAllocated = 0;
	PR_INFO("Prime Shutdown!");
}

void*
prMemAlloc(u64 size)
{
	s_TotalAllocated += size;
	return (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

void
prMemFree(void* memory, u64 size)
{
	if (memory) {
		s_TotalAllocated -= size;
		HeapFree(GetProcessHeap(), 0, memory);
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
prPlatformConsoleWrite(const PrString* message, PrLogLevel level)
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

	PrWideString* wide_str = prWideStringCreateFromPrString(message);
	DWORD number_written = 0;

	WriteConsoleW(console, 
		prWideStringGetBuffer(wide_str), 
		(DWORD)prWideStringGetLength(wide_str),
		&number_written, 0);

	prWideStringDestroy(wide_str);
	SetConsoleTextAttribute(console, 15);
}

f32
prTimeGet()
{
	u64 time;
	QueryPerformanceCounter((LARGE_INTEGER*)&time);
	return (f32)(time - s_StartTime) / s_ClockFrequency;
}

void
prTimeSleep(f64 milli_secs)
{
	Sleep((DWORD)milli_secs);
}

i32
prPlatformMultiByteToWideChar(
	const char* string,
	u32 string_len,
	wchar_t* wide_string)
{
	return MultiByteToWideChar(CP_UTF8, 0, string, -1, wide_string, string_len);
}

i32
prPlatformWideCharToMultiByte(
	const wchar_t* wide_string,
	u32 wide_string_len,
	char* string)
{
	return WideCharToMultiByte(CP_UTF8, 0, wide_string, -1, string, wide_string_len, 0, 0);
}

#endif // PR_PLATFORM_WINDOWS
