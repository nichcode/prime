
#include "pch.h"
#include "prime/prime.h"

static const char* levels[4] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: " };

void prime_log(u32 level, const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_format_args(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_format("%s%s\n", levels[level], formatted);
    prime_ConsoleWrite(level, out_msg);

    prime_free_string(formatted);
    prime_free_string(out_msg);
}

void prime_log_trace(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_format_args(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_format("%s%s\n", levels[PRIME_LEVEL_TRACE], formatted);
    prime_ConsoleWrite(PRIME_LEVEL_TRACE, out_msg);

    prime_free_string(formatted);
    prime_free_string(out_msg);
}

void prime_log_info(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_format_args(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_format("%s%s\n", levels[PRIME_LEVEL_INFO], formatted);
    prime_ConsoleWrite(PRIME_LEVEL_INFO, out_msg);

    prime_free_string(formatted);
    prime_free_string(out_msg);
}

void prime_log_warn(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_format_args(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_format("%s%s\n", levels[PRIME_LEVEL_WARN], formatted);
    prime_ConsoleWrite(PRIME_LEVEL_WARN, out_msg);

    prime_free_string(formatted);
    prime_free_string(out_msg);
}

void prime_log_error(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_format_args(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_format("%s%s\n", levels[PRIME_LEVEL_ERROR], formatted);
    prime_ConsoleWrite(PRIME_LEVEL_ERROR, out_msg);

    prime_free_string(formatted);
    prime_free_string(out_msg);
}

void prime_assert(b8 expr, const char* file, u32 line)
{
    if (expr) {}
    else {
        prime_log_error("Assertion failed in '%s' at line '%i'", file, line);
        PRIME_BREAK;
    }
}

void prime_assert_msg(b8 expr, const char* file, u32 line, const char* msg, ...)
{
    if (expr) {}
    else {
        va_list arg_ptr;
        va_start(arg_ptr, msg);
        char* formatted = prime_format_args(msg, arg_ptr);
        va_end(arg_ptr);

        char* out_msg = prime_format(
            "%s Assertion failed in %s at line %i \n%s", 
            levels[PRIME_LEVEL_ERROR], file, line, formatted);

        prime_ConsoleWrite(PRIME_LEVEL_ERROR, out_msg);

        prime_free_string(formatted);
        prime_free_string(out_msg);
        PRIME_BREAK;
    }
}
