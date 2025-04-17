
#include "PAL_pch.h"
#include "PAL/PAL_platform.h"
#include "PAL_wgl_context.h"

b8 PAL_Init()
{
    s_Instance = GetModuleHandleW(nullptr);
    WNDCLASSEXW wc = {};
    wc.cbClsExtra = 0;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.cbWndExtra = 0;
    wc.hbrBackground = NULL;
    wc.hCursor = LoadCursorW(s_Instance, IDC_ARROW);
    wc.hIcon = LoadIconW(s_Instance, IDI_APPLICATION);
    wc.hIconSm = LoadIconW(s_Instance, IDI_APPLICATION);
    wc.hInstance = s_Instance;
    wc.lpfnWndProc = _Win32Proc;
    wc.lpszClassName = s_ClassName;
    wc.lpszMenuName = NULL;
    wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

    ATOM success = RegisterClassExW(&wc);
    PAL_ASSERT(success, "Window Registration Failed");

    _InitInput();
    _WGLCreateDummyContext();

    int freetype_success = FT_Init_FreeType(&s_Library);
    PAL_ASSERT(!freetype_success, "Freetype initialization failed!");

    u64 time = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&s_ClockFrequency);
    QueryPerformanceCounter((LARGE_INTEGER*)&time);
    s_StartTime = time - s_ClockFrequency;

    PAL_INFO("Init");
    return PAL_PASSED;
}

void PAL_Shutdown()
{
    UnregisterClassW(s_ClassName, s_Instance);
    s_ActiveContext = nullptr;
    FT_Done_FreeType(s_Library);
    PAL_INFO("Shutdown");
}

char* PAL_Format(const char* fmt, ...)
{
    PAL_ASSERT(fmt, "fmt is null");
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char* result = PAL_FormatArgs(fmt, arg_ptr);
    va_end(arg_ptr);
    return result;
}

char* PAL_FormatArgs(const char* fmt, va_list args_list)
{
    PAL_ASSERT(fmt, "fmt is null");
    va_list list_copy;

#ifdef _MSC_VER
        list_copy = args_list;
#elif defined(P_PLATFORM_APPLE)
        list_copy = args_list;
#else
        __builtin_va_copy(list_copy, args_list);
#endif

    i32 length = vsnprintf(0, 0, fmt, list_copy);
    va_end(list_copy);
    char* result = new char[length + 1];
    vsnprintf(result, length + 1, fmt, args_list);
    result[length] = 0;
    return result;
}

char* PAL_ToString(const wchar_t* wstring)
{
    PAL_ASSERT(wstring, "wstring is null");
    int len = WideCharToMultiByte(CP_UTF8, 0, wstring, -1, nullptr, 0, 0, 0);
    if (len == 0) {
        return nullptr;
    }
    
    char* result = new char[len + 1];
    WideCharToMultiByte(CP_UTF8, 0, wstring, -1, result, len, 0, 0);
    return result;
}

wchar_t* PAL_ToWstring(const char* string)
{
    PAL_ASSERT(string, "string is null");
    int len = MultiByteToWideChar(CP_UTF8, 0, string, -1, nullptr, 0);
    if (len == 0) {
        return nullptr;
    }

    wchar_t* result = new wchar_t[len + sizeof(wchar_t)];
    MultiByteToWideChar(CP_UTF8, 0, string, -1, result, len);
    return result;
}

void PAL_FreeString(char* string)
{
    PAL_ASSERT(string, "string is null");
    delete[] string;
}

void PAL_FreeWstring(wchar_t* wstring)
{
    PAL_ASSERT(wstring, "wstring is null");
    delete[] wstring;
}

void _ConsoleWrite(u32 level, const char* message)
{
    b8 error = level > PAL_LogLevels_Warn;
    HANDLE console = NULL;
    static u8 levels[4] = { 8, 2, 6, 4 };

    if (error) {
        console = GetStdHandle(STD_ERROR_HANDLE);
    }
    else {
        console = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    SetConsoleTextAttribute(console, levels[level]);
    wchar_t* wstr = PAL_ToWstring(message);
    u64 len = wcslen(wstr);
    DWORD number_written = 0;

    WriteConsoleW(console, wstr, (DWORD)len, &number_written, 0);
    SetConsoleTextAttribute(console, 15);
    PAL_FreeWstring(wstr);
}

void* PAL_LoadLibrary(const char* dll)
{
    HMODULE result = LoadLibraryA(dll);
    PAL_ASSERT(result, "failed to load dll %s", dll);
    return result;
}

void* PAL_LoadProc(void* dll, const char* func_name)
{
    PAL_ASSERT(dll, "dll is null");
    HMODULE dll_lib = (HMODULE)dll;

    FARPROC proc = GetProcAddress((HMODULE)dll_lib, func_name);
    PAL_ASSERT(proc, "Failed to load function: %s from DLL", func_name);
    return (void*)proc;
}

void PAL_FreeLibrary(void* dll)
{
    PAL_ASSERT((HMODULE)dll, "dll is null");
    FreeLibrary((HMODULE)dll);
}

void PAL_Sleep(u64 milli_seconds)
{
    Sleep((DWORD)milli_seconds);
}

void PAL_SetUserData(void* data)
{
    s_UserData = data;
}

void* PAL_GetUserData()
{
    return s_UserData;
}

f32 PAL_GetTime()
{
    u64 time = 0;
    QueryPerformanceCounter((LARGE_INTEGER*)&time);
    return (f32)((time - s_StartTime) / s_ClockFrequency);
}