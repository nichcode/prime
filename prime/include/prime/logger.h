
#pragma once

#include "defines.h"

enum prime_log_level
{
    PRIME_LOG_LEVEL_TRACE,
    PRIME_LOG_LEVEL_INFO,
    PRIME_LOG_LEVEL_WARN,
    PRIME_LOG_LEVEL_ERROR
};

PRIME_API void prime_log(prime_log_level level, const char* msg, ...);
PRIME_API void prime_log_trace(const char* msg, ...);
PRIME_API void prime_log_info(const char* msg, ...);
PRIME_API void prime_log_warn(const char* msg, ...);
PRIME_API void prime_log_error(const char* msg, ...);

PRIME_API void prime_assert(b8 expr, const char* file, u32 line);
PRIME_API void prime_assert_msg(b8 expr, const char* file, u32 line, const char* msg);

#ifdef PRIME_CONFIG_DEBUG
#define PRIME_TRACE(...)                    prime_log_trace(__VA_ARGS__)
#define PRIME_INFO(...)                     prime_log_info(__VA_ARGS__)
#define PRIME_WARN(...)                     prime_log_warn(__VA_ARGS__)
#define PRIME_ERROR(...)                    prime_log_error(__VA_ARGS__)
#define PRIME_ASSERT(expr)                  prime_assert(expr, PRIME_FILE, PRIME_LINE)
#define PRIME_ASSERT_MSG(expr, message)     prime_assert_msg(expr, PRIME_FILE, PRIME_LINE, message)
#else
#define PRIME_TRACE(...)         
#define PRIME_DEBUG(...)         
#define PRIME_INFO(...)         
#define PRIME_WARN(...)          
#define PRIME_ERROR(...)               
#define PRIME_ASSERT(expr)
#define PRIME_ASSERT_MSG(expr, message)
#endif // PRIME_CONFIG_DEBUG