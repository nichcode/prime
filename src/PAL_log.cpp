
#include "PAL_pch.h"
#include "PAL/PAL_platform.h"

static const char* levels[4] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: " };

void PAL_Log(u32 level, const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = PAL_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = PAL_Format("%s%s\n", levels[level], formatted);
    _ConsoleWrite(level, out_msg);

    PAL_FreeString(formatted);
    PAL_FreeString(out_msg);
}

void PAL_LogTrace(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = PAL_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = PAL_Format("%s%s\n", levels[PAL_LogLevels_Trace], formatted);
    _ConsoleWrite(PAL_LogLevels_Trace, out_msg);

    PAL_FreeString(formatted);
    PAL_FreeString(out_msg);
}

void PAL_LogInfo(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = PAL_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = PAL_Format("%s%s\n", levels[PAL_LogLevels_Info], formatted);
    _ConsoleWrite(PAL_LogLevels_Info, out_msg);

    PAL_FreeString(formatted);
    PAL_FreeString(out_msg);
}

void PAL_LogWarn(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = PAL_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = PAL_Format("%s%s\n", levels[PAL_LogLevels_Warn], formatted);
    _ConsoleWrite(PAL_LogLevels_Warn, out_msg);

    PAL_FreeString(formatted);
    PAL_FreeString(out_msg);
}

void PAL_LogError(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = PAL_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = PAL_Format("%s%s\n", levels[PAL_LogLevels_Error], formatted);
    _ConsoleWrite(PAL_LogLevels_Error, out_msg);

    PAL_FreeString(formatted);
    PAL_FreeString(out_msg);
}

void PAL_Assert(b8 exPAL_, const char* file, u32 line, const char* msg, ...)
{
    if (exPAL_) {}
    else {
        va_list arg_ptr;
        va_start(arg_ptr, msg);
        char* formatted = PAL_FormatArgs(msg, arg_ptr);
        va_end(arg_ptr);

        char* out_msg = PAL_Format(
            "%s Assertion failed in %s at line %i \n%s", 
            levels[PAL_LogLevels_Error], file, line, formatted);

        _ConsoleWrite(PAL_LogLevels_Error, out_msg);

        PAL_FreeString(formatted);
        PAL_FreeString(out_msg);
        PAL_BREAK;
    }
}
