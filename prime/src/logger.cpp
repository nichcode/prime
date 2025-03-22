
#include "pch.h"

static const char* levels[4] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: " };

void prime_log(prime_log_level level, const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_string_format_args(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_string_format("%s%s\n", levels[level], formatted);
    consoleWrite(level, out_msg);

    prime_string_free(formatted);
    prime_string_free(out_msg);
}

void prime_log_trace(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_string_format_args(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_string_format("%s%s\n", levels[PRIME_LOG_LEVEL_TRACE], formatted);
    consoleWrite(PRIME_LOG_LEVEL_TRACE, out_msg);

    prime_string_free(formatted);
    prime_string_free(out_msg);
}

void prime_log_info(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_string_format_args(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_string_format("%s%s\n", levels[PRIME_LOG_LEVEL_INFO], formatted);
    consoleWrite(PRIME_LOG_LEVEL_INFO, out_msg);

    prime_string_free(formatted);
    prime_string_free(out_msg);
}

void prime_log_warn(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_string_format_args(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_string_format("%s%s\n", levels[PRIME_LOG_LEVEL_WARN], formatted);
    consoleWrite(PRIME_LOG_LEVEL_WARN, out_msg);

    prime_string_free(formatted);
    prime_string_free(out_msg);
}

void prime_log_error(const char* msg, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    char* formatted = prime_string_format_args(msg, arg_ptr);
    va_end(arg_ptr);
    char* out_msg = prime_string_format("%s%s\n", levels[PRIME_LOG_LEVEL_ERROR], formatted);
    consoleWrite(PRIME_LOG_LEVEL_ERROR, out_msg);

    prime_string_free(formatted);
    prime_string_free(out_msg);
}

void prime_assert(b8 expr, const char* file, u32 line)
{
    if (expr) {}
    else {
        char* out_msg = prime_string_format("Assertion failed in '%s' at line '%i'", file, line);
        prime_log_error(out_msg);
        PRIME_BREAK;
    }
}

void prime_assert_msg(b8 expr, const char* file, u32 line, const char* msg)
{
    if (expr) {}
    else {
        char* out_msg = prime_string_format("Assertion failed in '%s' at line '%i' \n'%s'", file, line, msg);
        prime_log_error(out_msg);
        PRIME_BREAK;
    }
}
