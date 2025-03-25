
#pragma once

#include "API.h"

PRIME_API void primeLog(primeLogLevel level, const char* msg, ...);
PRIME_API void primeLogTrace(const char* msg, ...);
PRIME_API void primeLogInfo(const char* msg, ...);
PRIME_API void primeLogWarn(const char* msg, ...);
PRIME_API void primeLogError(const char* msg, ...);

PRIME_API void primeAssert(b8 expr, const char* file, u32 line);
PRIME_API void primeAssertMsg(b8 expr, const char* file, u32 line, const char* msg, ...);

#ifdef PRIME_CONFIG_DEBUG
#define PRIME_TRACE(...)                    primeLogTrace(__VA_ARGS__)
#define PRIME_INFO(...)                     primeLogInfo(__VA_ARGS__)
#define PRIME_WARN(...)                     primeLogWarn(__VA_ARGS__)
#define PRIME_ERROR(...)                    primeLogError(__VA_ARGS__)
#define PRIME_ASSERT(expr)                  primeAssert(expr, PRIME_FILE, PRIME_LINE)
#define PRIME_ASSERT_MSG(expr, ...)         primeAssertMsg(expr, PRIME_FILE, PRIME_LINE, __VA_ARGS__)
#else
#define PRIME_TRACE(...)         
#define PRIME_DEBUG(...)         
#define PRIME_INFO(...)         
#define PRIME_WARN(...)          
#define PRIME_ERROR(...)               
#define PRIME_ASSERT(expr)
#define PRIME_ASSERT_MSG(expr, message)
#endif // PRIME_CONFIG_DEBUG