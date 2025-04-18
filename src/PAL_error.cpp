
#include "PAL_pch.h"
#include "PAL/PAL_platform.h"

static std::string s_MsgString;

char* _FormatArgs(const char* fmt, va_list args_list)
{
    if (!fmt) { return nullptr; }
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
    if (!result) { return nullptr; }

    vsnprintf(result, length + 1, fmt, args_list);
    result[length] = 0;
    return result;
}

char* _Format(const char* fmt, ...)
{
    if (!fmt) { return nullptr; }
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char* result = _FormatArgs(fmt, arg_ptr);
    va_end(arg_ptr);
    return result;
}

const char * PAL_GetError()
{
    return s_MsgString.c_str();
}

void PAL_ClearError()
{
    s_MsgString.clear();
}

void _SetError(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = _FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = _Format("%s\n", formatted);

    s_MsgString = std::string(out_msg);
    PAL_FreeString(formatted);
    PAL_FreeString(out_msg);

#ifdef PAL_CONFIG_DEBUG
    _ConsoleWrite(PAL_LogLevels_Error, s_MsgString.c_str());
    PAL_BREAK;
#endif // PAL_CONFIG_DEBUG
}