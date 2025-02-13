
#pragma once

#include "prime/prime_defines.h"
#include "prime/prime_log.h"

#ifdef PPLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

static HINSTANCE s_Instance;
static WINDOWPLACEMENT s_WndPlacement;

LRESULT CALLBACK
primeWin32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

#endif // PPLATFORM_WINDOWS

static u64 s_ClockFrequency = 0;
static u64 s_StartTime = 0;

#ifdef UNICODE
static const wchar_t* s_ClassName = L"PrimeWindowClass";
static const wchar_t* s_PropName = L"PrimeWindowHandle";
#else
static const char* s_ClassName = "PrimeWindowClass";
static const char* s_PropName = "PrimeWindowHandle";
#endif // UNICODE

static primeAllocator* s_Allocator = nullptr;

i32
primeMultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);

i32
primeWcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

char*
primeStringFormatSys(const char* fmt, ...);

void
primeStringFreeSys(char* string);

void
primeConsoleWrite(primeLogLevel level, const char* out_msg);