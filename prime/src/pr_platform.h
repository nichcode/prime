#pragma once

#include "prime/pr_log.h"

struct PrString;
struct PrDevice;
struct PrContext;
struct PrWindow;

void
prPlatformConsoleWrite(const PrString* message, PrLogLevel level);

i32 
prPlatformMultiByteToWideChar(
    const char* string,
    u32 string_len,
    wchar_t* wide_string);

i32
prPlatformWideCharToMultiByte(
    const wchar_t* wide_string,
    u32 wide_string_len,
    char* string);