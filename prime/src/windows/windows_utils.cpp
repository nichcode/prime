
#include "windows_API.h"
#include "prime_utils.h"
#include "prime/core/fmt.h"

namespace prime::utils {

    i32 multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr)
    {
        return MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, str_len);
    }

    i32 wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str)
    {
        return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, wstr_len, 0, 0);
    }

    void consoleWrite(LogLevel level, const char* msg)
    {
        b8 error = level > LogLevelWarn;
        HANDLE console = NULL;
        static u8 levels[4] = { 8, 2, 6, 4 };

        if (error) {
            console = GetStdHandle(STD_ERROR_HANDLE);
        }
        else {
            console = GetStdHandle(STD_OUTPUT_HANDLE);
        }

        SetConsoleTextAttribute(console, levels[level]);
        wstr wide_string = core::toWideString(msg);
        DWORD number_written = 0;

        WriteConsoleW(console, wide_string.c_str(), (DWORD)wide_string.length(), &number_written, 0);
        SetConsoleTextAttribute(console, 15);
    }

} // namespace prime::utils
