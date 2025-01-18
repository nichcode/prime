#pragma once

#include "prime/pr_log.h"
#include "prime/pr_native.h"

struct PrString;
struct PrWindow;
struct PrDriverContext;

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


#ifdef PR_PLATFORM_WINDOWS

void
prPlatformWin32WindowSetContext(PrWindow* window, PrDriverContext* context);

b8
prPlatformWin32HasContext(PrWindow* window);

#endif // PR_PLATFORM_WINDOWS