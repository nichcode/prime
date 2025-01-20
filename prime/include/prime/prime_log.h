#pragma once

#include "prime_defines.h"

PRIME_API void
prime_Log(prime_LogLevel level, const char* message, ...);

PRIME_INLINE void
prime_LogTrace(const char* message, ...)
{
    prime_Log(prime_LogLevelTrace, message);
}

PRIME_INLINE void
prime_LogInfo(const char* message, ...)
{
    prime_Log(prime_LogLevelInfo, message);
}

PRIME_INLINE void
prime_LogWarn(const char* message, ...)
{
    prime_Log(prime_LogLevelWarn, message);
}

PRIME_INLINE void
prime_LogError(const char* message, ...)
{
    prime_Log(prime_LogLevelError, message);
}

PRIME_INLINE void
prime_LogFatal(const char* message, ...)
{
    prime_Log(prime_LogLevelFatal, message);
}

PRIME_API void
prime_Assert(bool expr, const char* file, u32 line);

PRIME_API void
prime_AssertMsg(bool expr, const char* file, u32 line, const char* message);

PRIME_API void
prime_LogString(prime_String* string);

PRIME_API void
prime_LogWString(prime_WString* wide_string);

#ifdef PRIME_CONFIG_DEBUG
#define PRIME_TRACE(message, ...)           prime_LogTrace(message, __VA_ARGS__)
#define PRIME_INFO(message, ...)            prime_LogInfo(message,  __VA_ARGS__)
#define PRIME_WARN(message, ...)            prime_LogWarn(message,  __VA_ARGS__)
#define PRIME_ERROR(message, ...)           prime_LogError(message, __VA_ARGS__)
#define PRIME_FATAL(message, ...)           prime_LogFatal(message, __VA_ARGS__)
#define PRIME_ASSERT(expr)                  prime_Assert(expr, PRIME_FILE, PRIME_LINE)
#define PRIME_ASSERT_MSG(expr, message)     prime_AssertMsg(expr, PRIME_FILE, PRIME_LINE, message)
#define PRIME_LOG_STRING(string)            prime_LogString(string)
#define PRIME_LOG_WSTRING(wide_string)      prime_LogWString(wide_string)
#else
#define PRIME_TRACE(message, ...)         
#define PRIME_DEBUG(message, ...)         
#define PRIME_INFO(message, ...)         
#define PRIME_WARN(message, ...)          
#define PRIME_ERROR(message, ...)         
#define PRIME_FATAL(message, ...)        
#define PRIME_ASSERT(expr)
#define PRIME_ASSERT_MSG(expr, message)
#define PRIME_LOG_STRING(string)
#define PRIME_LOG_WSTRING(wide_string)
#endif // PRIME_CONFIG_DEBUG