
#include "prime/string.h"
#include "utils.h"
#include "pch.h"

// TODO: remove
#define PRIME_ASSERT_MSG(expr, message) 

char* prime_string_format_args(const char* fmt, va_list args_list)
{
    PRIME_ASSERT_MSG(fmt, "fmt is null");
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

char* prime_string_format(const char* fmt, ...)
{
    PRIME_ASSERT_MSG(fmt, "fmt is null");
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char* result = prime_string_format_args(fmt, arg_ptr);
    va_end(arg_ptr);
    return result;
}

char* prime_wstring_tostring(const wchar_t* wstring)
{
    PRIME_ASSERT_MSG(wstring, "wstring is null");
    int len = wcharToMultibyte(wstring, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }
    char* result = new char[len + 1];
    wcharToMultibyte(wstring, len, result);
    return result;
}

wchar_t* prime_string_towstring(const char* string)
{
    PRIME_ASSERT_MSG(string, "string is null");
    int len = multibyteToWchar(string, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }
    wchar_t* result = new wchar_t[sizeof(wchar_t) * len];
    multibyteToWchar(string, len, result);
    return result;
}

void prime_wstring_free(wchar_t* wstring)
{
    if (wstring) {
        delete[] wstring;
    }
}

void prime_string_free(char* string)
{
    if (string) {
        delete[] string;
    }
}
