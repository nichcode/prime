
#include "prime/prime_log.h"
#include "prime_utils.h"

#include <stdarg.h>
#include <stdio.h>

void
prime_Log(primeLogLevel level, const char* message, ...)
{
	static const char* levels[5] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: ", "[FATAL]: " };

	va_list arg_ptr;
	va_start(arg_ptr, message);
	char* formatted = prime_StringFormatSys(message, arg_ptr);
	va_end(arg_ptr);

	char* out_msg = prime_StringFormatSys("%s%s\n", levels[level], formatted);

	prime_ConsoleWrite(level, out_msg);
	prime_StringFreeSys(formatted);
	prime_StringFreeSys(out_msg);
}

void
prime_Assert(bool expr, const char* file, u32 line)
{
	if (expr) {}
	else {
		char* str = prime_StringFormatSys("Assertion failed in '%s' at line '%i'", file, line);
		prime_Log(primeLogLevelError, str);
		prime_StringFreeSys(str);
		PBREAK;
	}
}

void
prime_AssertMsg(bool expr, const char* file, u32 line, const char* message)
{
	if (expr) {}
	else {
		char* str = prime_StringFormatSys("Assertion failed in '%s' at line '%i' \n'%s'", file, line, message);
		prime_Log(primeLogLevelError, str);
		prime_StringFreeSys(str);
		PBREAK;
	}
}