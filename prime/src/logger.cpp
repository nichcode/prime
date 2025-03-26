
#include "pch.h"

static const char* levels[4] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: " };

void primeLog(primeLogLevel level, const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = primeFormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = primeFormat("%s%s\n", levels[level], formatted);
    consoleWrite(level, out_msg);

    primeStringFree(formatted);
    primeStringFree(out_msg);
}

void primeLogTrace(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = primeFormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = primeFormat("%s%s\n", levels[primeLogLevels_Trace], formatted);
    consoleWrite(primeLogLevels_Trace, out_msg);

    primeStringFree(formatted);
    primeStringFree(out_msg);
}

void primeLogInfo(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = primeFormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = primeFormat("%s%s\n", levels[primeLogLevels_Info], formatted);
    consoleWrite(primeLogLevels_Info, out_msg);

    primeStringFree(formatted);
    primeStringFree(out_msg);
}

void primeLogWarn(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = primeFormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = primeFormat("%s%s\n", levels[primeLogLevels_Warn], formatted);
    consoleWrite(primeLogLevels_Warn, out_msg);

    primeStringFree(formatted);
    primeStringFree(out_msg);
}

void primeLogError(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = primeFormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = primeFormat("%s%s\n", levels[primeLogLevels_Error], formatted);
    consoleWrite(primeLogLevels_Error, out_msg);

    primeStringFree(formatted);
    primeStringFree(out_msg);
}

void primeAssert(b8 expr, const char* file, u32 line)
{
    if (expr) {}
    else {
        char* out_msg = primeFormat("Assertion failed in '%s' at line '%i'", file, line);
        primeLogError(out_msg);
        PRIME_BREAK;
    }
}

void primeAssertMsg(b8 expr, const char* file, u32 line, const char* msg, ...)
{
    if (expr) {}
    else {
        va_list arg_ptr;
        va_start(arg_ptr, msg);
        char* formatted = primeFormatArgs(msg, arg_ptr);
        va_end(arg_ptr);

        char* out_msg = primeFormat(
            "%s Assertion failed in %s at line %i \n%s", 
            levels[primeLogLevels_Error], file, line, formatted);

        consoleWrite(primeLogLevels_Error, out_msg);
        PRIME_BREAK;
    }
}
