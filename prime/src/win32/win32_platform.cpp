
#include "pch.h"
#include "prime/platform.h"
#include "wgl_context.h"

b8 prInit()
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
    PR_ASSERT(success, "Window Registration Failed");

    _InitInput();
    _WGLCreateDummyContext();
    PR_INFO("Init");
    return PR_PASSED;
}

void prShutdown()
{
    UnregisterClassW(s_ClassName, s_Instance);
    s_ActiveContext = nullptr;
    PR_INFO("Shutdown");
}

char* prFormat(const char* fmt, ...)
{
    PR_ASSERT(fmt, "fmt is null");
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char* result = prFormatArgs(fmt, arg_ptr);
    va_end(arg_ptr);
    return result;
}

char* prFormatArgs(const char* fmt, va_list args_list)
{
    PR_ASSERT(fmt, "fmt is null");
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

char* prToString(const wchar_t* wstring)
{
    PR_ASSERT(wstring, "wstring is null");
    int len = WideCharToMultiByte(CP_UTF8, 0, wstring, -1, nullptr, 0, 0, 0);
    if (len == 0) {
        return nullptr;
    }
    
    char* result = new char[len + 1];
    WideCharToMultiByte(CP_UTF8, 0, wstring, -1, result, len, 0, 0);
    return result;
}

wchar_t* prToWstring(const char* string)
{
    PR_ASSERT(string, "string is null");
    int len = MultiByteToWideChar(CP_UTF8, 0, string, -1, nullptr, 0);
    if (len == 0) {
        return nullptr;
    }

    wchar_t* result = new wchar_t[len + sizeof(wchar_t)];
    MultiByteToWideChar(CP_UTF8, 0, string, -1, result, len);
    return result;
}

void prFreeString(char* string)
{
    PR_ASSERT(string, "string is null");
    delete[] string;
}

void prFreeWstring(wchar_t* wstring)
{
    PR_ASSERT(wstring, "wstring is null");
    delete[] wstring;
}

void _ConsoleWrite(u32 level, const char* message)
{
    b8 error = level > prLogLevels_Warn;
    HANDLE console = NULL;
    static u8 levels[4] = { 8, 2, 6, 4 };

    if (error) {
        console = GetStdHandle(STD_ERROR_HANDLE);
    }
    else {
        console = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    SetConsoleTextAttribute(console, levels[level]);
    wchar_t* wstr = prToWstring(message);
    u64 len = wcslen(wstr);
    DWORD number_written = 0;

    WriteConsoleW(console, wstr, (DWORD)len, &number_written, 0);
    SetConsoleTextAttribute(console, 15);
    prFreeWstring(wstr);
}

void* prLoadLibrary(const char* dll)
{
    HMODULE result = LoadLibraryA(dll);
    PR_ASSERT(result, "failed to load dll %s", dll);
    return result;
}

void* prLoadProc(void* dll, const char* func_name)
{
    PR_ASSERT(dll, "dll is null");
    HMODULE dll_lib = (HMODULE)dll;

    FARPROC proc = GetProcAddress((HMODULE)dll_lib, func_name);
    PR_ASSERT(proc, "Failed to load function: %s from DLL", func_name);
    return (void*)proc;
}

void prFreeLibrary(void* dll)
{
    PR_ASSERT((HMODULE)dll, "dll is null");
    FreeLibrary((HMODULE)dll);
}

void prSetUserData(void* data)
{
    s_UserData = data;
}

void* prGetUserData()
{
    return s_UserData;
}