
#pragma once

#include "prime/defines.h"
#include "prime/logger.h"

i32 multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);
i32 wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

void consoleWrite(prime_log_level level, const char* msg);