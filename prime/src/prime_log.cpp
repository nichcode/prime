
#include "pch.h"
#include "prime/prime.h"

static const char* levels[4] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: " };

void prime_Log(prime_LogLevel level, const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_Format("%s%s\n", levels[level], formatted);
    consoleWrite(level, out_msg);
}

void prime_LogTrace(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_Format("%s%s\n", levels[PRIME_LEVEL_TRACE], formatted);
    consoleWrite(PRIME_LEVEL_TRACE, out_msg);
}

void prime_LogInfo(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_Format("%s%s\n", levels[PRIME_LEVEL_INFO], formatted);
    consoleWrite(PRIME_LEVEL_INFO, out_msg);
}

void prime_LogWarn(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_Format("%s%s\n", levels[PRIME_LEVEL_WARN], formatted);
    consoleWrite(PRIME_LEVEL_WARN, out_msg);
}

void prime_LogError(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_FormatArgs(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_Format("%s%s\n", levels[PRIME_LEVEL_ERROR], formatted);
    consoleWrite(PRIME_LEVEL_ERROR, out_msg);
}

void prime_Assert(b8 expr, const char* file, u32 line)
{
    if (expr) {}
    else {
        char* out_msg = prime_Format("Assertion failed in '%s' at line '%i'", file, line);
        prime_LogError(out_msg);
        PRIME_BREAK;
    }
}

void prime_AssertMsg(b8 expr, const char* file, u32 line, const char* msg, ...)
{
    if (expr) {}
    else {
        va_list arg_ptr;
        va_start(arg_ptr, msg);
        char* formatted = prime_FormatArgs(msg, arg_ptr);
        va_end(arg_ptr);

        char* out_msg = prime_Format(
            "%s Assertion failed in %s at line %i \n%s", 
            levels[PRIME_LEVEL_ERROR], file, line, formatted);

        consoleWrite(PRIME_LEVEL_ERROR, out_msg);
        PRIME_BREAK;
    }
}
