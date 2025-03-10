
#include "prime/core/fmt.h"
#include "prime/core/logger.h"
#include "prime_utils.h"
#include <stdarg.h>

namespace prime::core {

    char* formatArgs(const char* fmt, va_list args_list)
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

    str toString(const wchar_t* wide_string)
    {
        PRIME_ASSERT_MSG(wide_string, "wide_string is null");
        int len = utils::wcharToMultibyte(wide_string, 0, nullptr);
        if (len == 0) {
            return nullptr;
        }
        char* buffer = new char[len + 1];
        utils::wcharToMultibyte(wide_string, len, buffer);

        str string(buffer);
        delete[] buffer;
        return string;
    }

    str toString(const wstr& wide_string)
    {
        return toString(wide_string.c_str());
    }

    wstr toWideString(const char* string)
    {
        PRIME_ASSERT_MSG(string, "string is null");
        int len = utils::multibyteToWchar(string, 0, nullptr);
        if (len == 0) {
            return nullptr;
        }
        wchar_t* buffer = new wchar_t[sizeof(wchar_t) * len];
        utils::multibyteToWchar(string, len, buffer);

        wstr wide_string(buffer);
        delete[] buffer;
        return wide_string;
    }

    wstr toWideString(const str& string)
    {
        return toWideString(string.c_str());
    }

    str format(const char* fmt, ...)
    {
        PRIME_ASSERT_MSG(fmt, "fmt is null");
        va_list arg_ptr;
        va_start(arg_ptr, fmt);
        char* result = formatArgs(fmt, arg_ptr);
        va_end(arg_ptr);

        str string(result);
        delete[] result;
        return string;
    }
    
} // namespace prime::utils

