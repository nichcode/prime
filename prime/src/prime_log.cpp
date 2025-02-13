
#include "prime/prime_log.h"
#include "prime_utils.h"

#include <stdarg.h>
#include <stdio.h>

void
primeLog(primeLogLevel level, const char* message, ...)
{
	static const char* levels[5] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: ", "[FATAL]: " };

	va_list arg_ptr;
	va_start(arg_ptr, message);
	char* formatted = primeStringFormatSys(message, arg_ptr);
	va_end(arg_ptr);

	char* out_msg = primeStringFormatSys("%s%s\n", levels[level], formatted);

	primeConsoleWrite(level, out_msg);
	primeStringFreeSys(formatted);
	primeStringFreeSys(out_msg);
}

void
primeAssert(bool expr, const char* file, u32 line)
{
	if (expr) {}
	else {
		char* str = primeStringFormatSys("Assertion failed in '%s' at line '%i'", file, line);
		primeLog(primeLogLevelError, str);
		primeStringFreeSys(str);
		PBREAK;
	}
}

void
primeAssertMsg(bool expr, const char* file, u32 line, const char* message)
{
	if (expr) {}
	else {
		char* str = primeStringFormatSys("Assertion failed in '%s' at line '%i' \n'%s'", file, line, message);
		primeLog(primeLogLevelError, str);
		primeStringFreeSys(str);
		PBREAK;
	}
}