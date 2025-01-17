
#include "pr_win32platform.h"

#ifdef PR_PLATFORM_WINDOWS

#include <memory>
#include <string>

#include "pr_platform.h"

b8
prInit()
{
	s_Instance = GetModuleHandle(nullptr);

	WNDCLASSEX wc = {};
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
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
	PR_INFO("Prime Initialized!");
	return PR_PASSED;
}

void
prShutdown()
{
	UnregisterClassA(s_ClassName, s_Instance);
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

#endif // PR_PLATFORM_WINDOWS
