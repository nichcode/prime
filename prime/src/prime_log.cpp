
#include "prime/prime_log.h"
#include "prime/prime_string.h"
#include "prime_utils.h"

#include <stdarg.h>
#include <stdio.h>

void
prime_Log(prime_LogLevel level, const char* message, ...)
{
	static const char* levels[5] = { "[TRACE]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: ", "[FATAL]: " };

	va_list arg_ptr;
	va_start(arg_ptr, message);
	prime_String* formatted = prime_StringFormat(message, arg_ptr);
	va_end(arg_ptr);

	prime_String* out_msg = prime_StringFormat("%s%s\n", levels[level], prime_StringGetCstr(formatted));

	prime_ConsoleWrite(out_msg, level);

	prime_StringDestroy(formatted);
	prime_StringDestroy(out_msg);
}

void 
prime_Assert(bool expr, const char* file, u32 line)
{
	if (expr) {}
	else {
		prime_String* str = prime_StringFormat("Assertion failed in '%s' at line '%i'", file, line);
		prime_LogError(prime_StringGetCstr(str));
		prime_StringDestroy(str);
		PRIME_BREAK;
	}
}

void 
prime_AssertMsg(bool expr, const char* file, u32 line, const char* message)
{
	if (expr) {}
	else {
		prime_String* str = prime_StringFormat("Assertion failed in '%s' at line '%i' \n'%s'", file, line, message);
		prime_LogError(prime_StringGetCstr(str));
		prime_StringDestroy(str);
		PRIME_BREAK;
	}
}

void
prime_LogString(prime_String* string)
{
	prime_LogInfo(prime_StringGetCstr(string));
}

void
prime_LogWString(prime_WString* wide_string)
{
	prime_String* string = prime_StringFromWString(wide_string);
	prime_LogString(string);
	prime_StringDestroy(string);
}