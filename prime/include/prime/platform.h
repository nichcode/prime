
#pragma once

#include "defines.h"
#include "log.h"
#include <stdarg.h>

PR_API b8 prInit();
PR_API void prShutdown();

PR_API char* prFormat(const char* fmt, ...);
PR_API char* prFormatArgs(const char* fmt, va_list args_list);

PR_API char* prToString(const wchar_t* wstring);
PR_API wchar_t* prToWstring(const char* string);

PR_API void prFreeString(char* string);
PR_API void prFreeWstring(wchar_t* wstring);
PR_API void prConsoleWrite(u32 level, const char* message);

PR_API void* prLoadLibrary(const char* dll);
PR_API void* prLoadProc(void* dll, const char* func_name);
PR_API void prFreeLibrary(void* dll);
