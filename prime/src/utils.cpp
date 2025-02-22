
#include "prime/utils.h"
#include "prime/logger.h"
#include "prime/platform.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

namespace prime {

    void 
    stringFree(char* string)
    {
        PASSERT_MSG(string, "string is null");
        u64 length = strlen(string);
        Platform::free(string, length + 1);
    }

    char* 
    Utils::format(const char* fmt, va_list args_list)
    {
        PASSERT_MSG(fmt, "fmt is null");
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

        char* result = Platform::alloc<char>(length + 1);
        PASSERT_MSG(result, "buffer allocation failed");
        vsnprintf(result, length + 1, fmt, args_list);
        result[length] = 0;
        return result;
    }

    str 
    Utils::format(const char* fmt, ...)
    {
        PASSERT_MSG(fmt, "fmt is null");
        va_list arg_ptr;
        va_start(arg_ptr, fmt);
        char* result = format(fmt, arg_ptr);
        PASSERT_MSG(result, "buffer allocation failed");
        va_end(arg_ptr);

        str string(result);
        stringFree(result);
        return string;
    }
    
} // namespace prime