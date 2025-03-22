
#include "utils.h"
#include "pch.h"

i32 multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr)
{
    return MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, str_len);
}

i32 wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str)
{
    return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, wstr_len, 0, 0);
}

void consoleWrite(prime_log_level level, const char* msg)
{
    b8 error = level > PRIME_LOG_LEVEL_WARN;
    HANDLE console = NULL;
    static u8 levels[4] = { 8, 2, 6, 4 };

    if (error) {
        console = GetStdHandle(STD_ERROR_HANDLE);
    }
    else {
        console = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    SetConsoleTextAttribute(console, levels[level]);
    wchar_t* wstr = prime_string_towstring(msg);
    u64 len = wcslen(wstr);
    DWORD number_written = 0;

    WriteConsoleW(console, wstr, (DWORD)len, &number_written, 0);
    SetConsoleTextAttribute(console, 15);
    prime_wstring_free(wstr);
}