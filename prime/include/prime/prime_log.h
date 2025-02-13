
#pragma once

#include "prime_defines.h"

enum primeLogLevel
{
	primeLogLevelTrace,
	primeLogLevelInfo,
	primeLogLevelWarn,
	primeLogLevelError,
	primeLogLevelFatal
};

PAPI void
prime_Log(primeLogLevel level, const char* message, ...);

PINLINE void
prime_LogTrace(const char* message, ...)
{
    prime_Log(primeLogLevelTrace, message);
}

PINLINE void
prime_LogInfo(const char* message, ...)
{
    prime_Log(primeLogLevelInfo, message);
}

PINLINE void
prime_LogWarn(const char* message, ...)
{
    prime_Log(primeLogLevelWarn, message);
}

PINLINE void
prime_LogError(const char* message, ...)
{
    prime_Log(primeLogLevelError, message);
}

PINLINE void
prime_LogFatal(const char* message, ...)
{
    prime_Log(primeLogLevelFatal, message);
}

PAPI void
prime_Assert(bool expr, const char* file, u32 line);

PAPI void
prime_AssertMsg(bool expr, const char* file, u32 line, const char* message);

#ifdef PCONFIG_DEBUG
#define PTRACE(message, ...)           prime_LogTrace(message, __VA_ARGS__)
#define PINFO(message, ...)            prime_Log(primeLogLevelInfo, message)
#define PWARN(message, ...)            prime_LogWarn(message,  __VA_ARGS__)
#define PERROR(message, ...)           prime_LogError(message, __VA_ARGS__)
#define PFATAL(message, ...)           prime_LogFatal(message, __VA_ARGS__)
#define PASSERT(expr)                  prime_Assert(expr, PFILE, PLINE)
#define PASSERT_MSG(expr, message)     prime_AssertMsg(expr, PFILE, PLINE, message)
#else
#define PTRACE(message, ...)         
#define PDEBUG(message, ...)               
#define PINFO(message, ...)                
#define PWARN(message, ...)          
#define PERROR(message, ...)         
#define PFATAL(message, ...)        
#define PASSERT(expr)
#define PASSERT_MSG(expr, message)
#endif // PCONFIG_DEBUG
