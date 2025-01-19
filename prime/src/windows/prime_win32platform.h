#pragma once

#include "prime/prime.h"

#ifdef PRIME_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>

static u64 s_TotalAllocated = 0;
static HINSTANCE s_Instance;
static const wchar_t* s_ClassName = L"PrWindowClass";
static const wchar_t* s_PropName = L"PrWindowHandle";
static u64 s_ClockFrequency = 0;
static u64 s_StartTime = 0;
static WINDOWPLACEMENT s_WndPlacement;

LRESULT CALLBACK
prime_WinProc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

#endif // PRIME_PLATFORM_WINDOWS
