
#pragma once

#include "defines.h"

enum prLogLevels_
{
    prLogLevels_Trace,
    prLogLevels_Info,
    prLogLevels_Warn,
    prLogLevels_Error,
};

PR_API void prLog(u32 level, const char* msg, ...);
PR_API void prLogTrace(const char* msg, ...);
PR_API void prLogInfo(const char* msg, ...);

PR_API void prLogWarn(const char* msg, ...);
PR_API void prLogError(const char* msg, ...);
PR_API void prAssert(b8 expr, const char* file, u32 line, const char* msg, ...);

#ifdef PR_CONFIG_DEBUG
#define PR_TRACE(...)                    prLogTrace(__VA_ARGS__)
#define PR_INFO(...)                     prLogInfo(__VA_ARGS__)
#define PR_WARN(...)                     prLogWarn(__VA_ARGS__)
#define PR_ERROR(...)                    prLogError(__VA_ARGS__)
#define PR_ASSERT(expr, ...)             prAssert(expr, PR_FILE, PR_LINE, __VA_ARGS__)
#else
#define PR_TRACE(...)                
#define PR_INFO(...)         
#define PR_WARN(...)          
#define PR_ERROR(...)               
#define PR_ASSERT(expr, ...)
#endif // PR_CONFIG_DEBUG