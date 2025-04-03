
#include "pch.h"
#include "wgl_context.h"
#include "prime/prime.h"
#include "prime_utils.h"

namespace prime {
        
    void windowsInit()
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
        wc.lpfnWndProc = windowsProc;
        wc.lpszClassName = s_ClassName;
        wc.lpszMenuName = NULL;
        wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

        ATOM success = RegisterClassExW(&wc);
        PRIME_ASSERT_MSG(success, "Window Registration Failed");

        if (prime::s_Data.type == PRIME_DEVICE_OPENGL) {
            prime::wglCreateDummyContext();
        }
    }

    void windowsShutdown()
    {
        UnregisterClassW(s_ClassName, s_Instance);
    }

    i32 multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr)
    {
        return MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, str_len);
    }

    i32 wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str)
    {
        return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, wstr_len, 0, 0);
    }

    void consoleWrite(u32 level, const char* msg)
    {
        b8 error = level > PRIME_LEVEL_WARN;
        HANDLE console = NULL;
        static u8 levels[4] = { 8, 2, 6, 4 };

        if (error) {
            console = GetStdHandle(STD_ERROR_HANDLE);
        }
        else {
            console = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        SetConsoleTextAttribute(console, levels[level]);
        wchar_t* wstr = prime_to_wstring(msg);
        u64 len = wcslen(wstr);
        DWORD number_written = 0;

        WriteConsoleW(console, wstr, (DWORD)len, &number_written, 0);
        SetConsoleTextAttribute(console, 15);

    }
    
} // namespace prime

void* prime_load_library(const char* dll)
{
    HMODULE result = LoadLibraryA(dll);
    PRIME_ASSERT_MSG(result, "failed to load dll %s", dll);
    return result;
}

void* prime_load_proc(void* dll, const char* func_name)
{
    PRIME_ASSERT_MSG(dll, "dll is null");
    HMODULE dll_lib = (HMODULE)dll;

    FARPROC proc = GetProcAddress((HMODULE)dll_lib, func_name);
    PRIME_ASSERT_MSG(proc, "Failed to load function: %s from DLL", func_name);
    return (void*)proc;
}

void prime_free_library(void* dll)
{
    PRIME_ASSERT_MSG((HMODULE)dll, "dll is null");
    FreeLibrary((HMODULE)dll);
}