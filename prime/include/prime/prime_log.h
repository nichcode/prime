
#pragma once

#include "prime_defines.h"

using prime_LogLevel = u32;

enum prime_LogLevels
{
    PRIME_LEVEL_TRACE,
    PRIME_LEVEL_INFO,
    PRIME_LEVEL_WARN,
    PRIME_LEVEL_ERROR
};

PRIME_API void prime_Log(prime_LogLevel level, const char* msg, ...);
PRIME_API void prime_LogTrace(const char* msg, ...);
PRIME_API void prime_LogInfo(const char* msg, ...);
PRIME_API void prime_LogWarn(const char* msg, ...);
PRIME_API void prime_LogError(const char* msg, ...);

PRIME_API void prime_Assert(b8 expr, const char* file, u32 line);
PRIME_API void prime_AssertMsg(b8 expr, const char* file, u32 line, const char* msg, ...);

#ifdef PRIME_CONFIG_DEBUG
#define PRIME_TRACE(...)                    prime_LogTrace(__VA_ARGS__)
#define PRIME_INFO(...)                     prime_LogInfo(__VA_ARGS__)
#define PRIME_WARN(...)                     prime_LogWarn(__VA_ARGS__)
#define PRIME_ERROR(...)                    prime_LogError(__VA_ARGS__)
#define PRIME_ASSERT(expr)                  prime_Assert(expr, PRIME_FILE, PRIME_LINE)
#define PRIME_ASSERT_MSG(expr, ...)         prime_AssertMsg(expr, PRIME_FILE, PRIME_LINE, __VA_ARGS__)
#else
#define PRIME_TRACE(...)         
#define PRIME_DEBUG(...)         
#define PRIME_INFO(...)         
#define PRIME_WARN(...)          
#define PRIME_ERROR(...)               
#define PRIME_ASSERT(expr)
#define PRIME_ASSERT_MSG(expr, message)
#endif // PRIME_CONFIG_DEBUG