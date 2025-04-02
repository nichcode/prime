
#include "pch.h"
#include "prime_utils.h"
#include "prime/prime.h"

#ifdef PRIME_PLATFORM_WINDOWS
#include "windows/windows_API.h"
#endif // PRIME_PLATFORM_WINDOWS

b8 prime_init(u32 type)
{
    prime::s_Data.type = type;
    prime::s_Data.allocator.init();
#ifdef PRIME_PLATFORM_WINDOWS
    prime::windowsInit();
#endif // PRIME_PLATFORM_WINDOWS
    return PRIME_PASSED;
}

void prime_shutdown()
{
    prime::s_Data.allocator.shutdown();
#ifdef PRIME_PLATFORM_WINDOWS
    prime::windowsShutdown();
#endif // PRIME_PLATFORM_WINDOWS
}

char* prime_format(const char* fmt, ...)
{
    PRIME_ASSERT_MSG(fmt, "fmt is null");
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char* result = prime_format_args(fmt, arg_ptr);
    va_end(arg_ptr);
    return result;
}

char* prime_format_args(const char* fmt, va_list args_list)
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
    char* result = (char*)prime::s_Data.allocator.allocate(length + 1);
    vsnprintf(result, length + 1, fmt, args_list);
    result[length] = 0;
    return result;
}

char* prime_to_string(const wchar_t* wstring)
{
    PRIME_ASSERT_MSG(wstring, "wstring is null");
    int len = prime::wcharToMultibyte(wstring, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }
    
    char* result = (char*)prime::s_Data.allocator.allocate(len + 1);
    prime::wcharToMultibyte(wstring, len, result);
    return result;
}

wchar_t* prime_to_wstring(const char* string)
{
    PRIME_ASSERT_MSG(string, "string is null");
    int len = prime::multibyteToWchar(string, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }

    wchar_t* result = (wchar_t*)prime::s_Data.allocator.allocate(sizeof(wchar_t) * len);
    prime::multibyteToWchar(string, len, result);
    return result;
}

f32 prime_sqrt(f32 number)
{
    return sqrtf(number);
}

f32 prime_tan(f32 number)
{
    return tanf(number);
}

f32 prime_cos(f32 number)
{
    return cosf(number);
}

f32 prime_sin(f32 number)
{
    return sinf(number);
}