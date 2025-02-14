
#include "prime/prime_platform.h"
#include "prime_utils.h"
#include "prime/prime_memory.h"
#include "prime/prime_string.h"
#include "prime/prime_time.h"
#include "prime_wglcontext.h"

static u64 s_UsedMemory = 0;

u8
primePlatformInit()
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
	wc.lpfnWndProc = primeWin32Proc;
	wc.lpszClassName = s_ClassName;
	wc.lpszMenuName = NULL;
	wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

	ATOM success = RegisterClassEx(&wc);
	PASSERT_MSG(success, "Window Registration Failed");

	QueryPerformanceFrequency((LARGE_INTEGER*)&s_ClockFrequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&s_StartTime);

    primeWGLContextCreateDummy();
	
    PINFO("Prime Win32Platform Init");
    return 1;
}

void
primePlatformShutdown()
{
	UnregisterClass(s_ClassName, s_Instance);
	s_UsedMemory = 0;
    PINFO("Prime Win32Platform Shutdown");
}

void*
primeMemoryAlloc(u64 size)
{
    PASSERT_MSG(size, "size is invalid");
    s_UsedMemory += size;
	return (void*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

void
primeMemoryFree(void* memory, u64 size)
{
    PASSERT_MSG(memory, "memory is null");
    s_UsedMemory -= size;
	HeapFree(GetProcessHeap(), 0, memory);
	memory = nullptr;
}

void
primeMemorySet(void* memory, i32 value, u64 size)
{
    PASSERT_MSG(memory, "memory is null");
    memset(memory, value, size);
}

void
primeMemoryZero(void* memory, u64 size)
{
    PASSERT_MSG(memory, "memory is null");
    memset(memory, 0, size);
}

void
primeMemoryCopy(void* dest_memory, void* src_memory, u64 size)
{
    PASSERT_MSG(dest_memory, "dest_memory is null");
    PASSERT_MSG(src_memory, "src_memory is null");
    memcpy(dest_memory, src_memory, size);
}

i32
primeMultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr)
{
    return MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, str_len);
}

i32
primeWcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str)
{
    return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, wstr_len, 0, 0);
}

void
primeConsoleWrite(primeLogLevel level, const char* out_msg)
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
	wchar_t* wstr = primeStringToWstring(out_msg);
	DWORD number_written = 0;

	WriteConsoleW(console, wstr, (DWORD)wcslen(wstr), &number_written, 0);
	primeWstringFree(wstr);
	SetConsoleTextAttribute(console, 15);
}

f32
primeTimeGet()
{
	u64 time;
	QueryPerformanceCounter((LARGE_INTEGER*)&time);
	return (f32)(time - s_StartTime) / s_ClockFrequency;
}

void
primeTimeSleep(f64 milli_seconds)
{
	Sleep((DWORD)milli_seconds);
}