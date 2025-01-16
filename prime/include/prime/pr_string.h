#pragma once

#include "pr_defines.h"
#include "pr_log.h"

struct PrString;
struct PrAllocator;

PR_API PrString*
prStringCreate(const char* string);

PR_API PrString*
prStringCreateA(PrAllocator* allocator, const char* string);

PR_API void
prStringDestroy(PrString* string);

PR_API PrString*
prStringCopy(const PrString* string);

PR_API PrString*
prStringCopyA(PrAllocator* allocator, const PrString* string);

PR_API const char*
prStringGetBuffer(PrString* string);

PR_API u64
prStringGetLength(PrString* string);

PR_API PrString*
prStringFormat(const char* fmt, ...);

PR_API PrString*
prStringFormatArgs(const char* fmt, char* va_listp);

PR_API void
prStringLog(PrString* string);

#ifdef PR_CONFIG_DEBUG
#define PR_STRING_LOG(string)     prStringLog(string)
#else
#define PR_STRING_LOG(message, ...)         
#endif // PR_CONFIG_DEBUG