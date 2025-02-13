
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
primeLog(primeLogLevel level, const char* message, ...);

PINLINE void
primeLogTrace(const char* message, ...)
{
    primeLog(primeLogLevelTrace, message);
}

PINLINE void
primeLogInfo(const char* message, ...)
{
    primeLog(primeLogLevelInfo, message);
}

PINLINE void
primeLogWarn(const char* message, ...)
{
    primeLog(primeLogLevelWarn, message);
}

PINLINE void
primeLogError(const char* message, ...)
{
    primeLog(primeLogLevelError, message);
}

PINLINE void
primeLogFatal(const char* message, ...)
{
    primeLog(primeLogLevelFatal, message);
}

PAPI void
primeAssert(bool expr, const char* file, u32 line);

PAPI void
primeAssertMsg(bool expr, const char* file, u32 line, const char* message);

#ifdef PCONFIG_DEBUG
#define PTRACE(message, ...)           primeLogTrace(message, __VA_ARGS__)
#define PINFO(message, ...)            primeLog(primeLogLevelInfo, message)
#define PWARN(message, ...)            primeLogWarn(message,  __VA_ARGS__)
#define PERROR(message, ...)           primeLogError(message, __VA_ARGS__)
#define PFATAL(message, ...)           primeLogFatal(message, __VA_ARGS__)
#define PASSERT(expr)                  primeAssert(expr, PFILE, PLINE)
#define PASSERT_MSG(expr, message)     primeAssertMsg(expr, PFILE, PLINE, message)
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
