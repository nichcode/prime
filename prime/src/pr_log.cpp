
#include "prime/pr_log.h"
#include "prime/pr_string.h"
#include "pr_platform.h"

#include <stdarg.h>
#include <stdio.h>

void
prLog(PrLogLevel level, const char* message, ...)
{
	static const char* levels[5] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: ", "[FATAL]: " };

	va_list arg_ptr;
	va_start(arg_ptr, message);
	PrString* formatted = prStringFormat(message, arg_ptr);
	va_end(arg_ptr);

	PrString* out_msg = prStringFormat("%s%s\n", levels[level], prStringGetBuffer(formatted));

	prPlatformConsoleWrite(prStringGetBuffer(out_msg), level);

	prStringDestroy(formatted);
	prStringDestroy(out_msg);
}

void 
prAssert(bool expr, const char* file, u32 line)
{
	if (expr) {}
	else {
		PrString* str = prStringFormat("Assertion failed in '%s' at line '%i'", file, line);
		prLogError(prStringGetBuffer(str));
		prStringDestroy(str);
		PR_BREAK;
	}
}

void 
prAssertMsg(bool expr, const char* file, u32 line, const char* message)
{
	if (expr) {}
	else {
		PrString* str = prStringFormat("Assertion failed in '%s' at line '%i' \n'%s'", file, line, message);
		prLogError(prStringGetBuffer(str));
		prStringDestroy(str);
		PR_BREAK;
	}
}
