#pragma once

#include "pr_defines.h"

enum PrLogLevel
{
    PrLogLevelTrace,
    PrLogLevelInfo,
    PrLogLevelWarn,
    PrLogLevelError,
    PrLogLevelFatal
};

PR_API void
prLog(PrLogLevel level, const char* message, ...);

PR_INLINE void
prLogTrace(const char* message, ...)
{
    prLog(PrLogLevelTrace, message);
}

PR_INLINE void
prLogInfo(const char* message, ...)
{
    prLog(PrLogLevelInfo, message);
}

PR_INLINE void
prLogWarn(const char* message, ...)
{
    prLog(PrLogLevelWarn, message);
}

PR_INLINE void
prLogError(const char* message, ...)
{
    prLog(PrLogLevelError, message);
}

PR_INLINE void
prLogFatal(const char* message, ...)
{
    prLog(PrLogLevelFatal, message);
}

PR_API void
prAssert(bool expr, const char* file, u32 line);

PR_API void
prAssertMsg(bool expr, const char* file, u32 line, const char* message);

#ifdef PR_CONFIG_DEBUG
#define PR_TRACE(message, ...)           prLogTrace(message, __VA_ARGS__)
#define PR_INFO(message, ...)            prLogInfo(message,  __VA_ARGS__)
#define PR_WARN(message, ...)            prLogWarn(message,  __VA_ARGS__)
#define PR_ERROR(message, ...)           prLogError(message, __VA_ARGS__)
#define PR_FATAL(message, ...)           prLogFatal(message, __VA_ARGS__)
#define PR_ASSERT(expr)                  prAssert(expr, PR_FILE, PR_LINE)
#define PR_ASSERT_MSG(expr, message)     prAssertMsg(expr, PR_FILE, PR_LINE, message)
#else
#define PR_TRACE(message, ...)         
#define PR_DEBUG(message, ...)         
#define PR_INFO(message, ...)         
#define PR_WARN(message, ...)          
#define PR_ERROR(message, ...)         
#define PR_FATAL(message, ...)        
#define PR_ASSERT(expr)
#define PR_ASSERT_MSG(expr, message)
#endif // PR_CONFIG_DEBUG