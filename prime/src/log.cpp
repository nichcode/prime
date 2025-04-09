
#include "pch.h"
#include "prime/platform.h"

static const char* levels[4] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: " };

void prLog(u32 level, const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prFormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prFormat("%s%s\n", levels[level], formatted);
    _ConsoleWrite(level, out_msg);

    prFreeString(formatted);
    prFreeString(out_msg);
}

void prLogTrace(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prFormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prFormat("%s%s\n", levels[prLogLevels_Trace], formatted);
    _ConsoleWrite(prLogLevels_Trace, out_msg);

    prFreeString(formatted);
    prFreeString(out_msg);
}

void prLogInfo(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prFormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prFormat("%s%s\n", levels[prLogLevels_Info], formatted);
    _ConsoleWrite(prLogLevels_Info, out_msg);

    prFreeString(formatted);
    prFreeString(out_msg);
}

void prLogWarn(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prFormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prFormat("%s%s\n", levels[prLogLevels_Warn], formatted);
    _ConsoleWrite(prLogLevels_Warn, out_msg);

    prFreeString(formatted);
    prFreeString(out_msg);
}

void prLogError(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prFormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prFormat("%s%s\n", levels[prLogLevels_Error], formatted);
    _ConsoleWrite(prLogLevels_Error, out_msg);

    prFreeString(formatted);
    prFreeString(out_msg);
}

void prAssert(b8 expr, const char* file, u32 line, const char* msg, ...)
{
    if (expr) {}
    else {
        va_list arg_ptr;
        va_start(arg_ptr, msg);
        char* formatted = prFormatArgs(msg, arg_ptr);
        va_end(arg_ptr);

        char* out_msg = prFormat(
            "%s Assertion failed in %s at line %i \n%s", 
            levels[prLogLevels_Error], file, line, formatted);

        _ConsoleWrite(prLogLevels_Error, out_msg);

        prFreeString(formatted);
        prFreeString(out_msg);
        PR_BREAK;
    }
}
