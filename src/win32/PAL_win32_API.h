
#pragma once

#include "PAL/PAL_defines.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

static HINSTANCE s_Instance;
static const wchar_t* s_ClassName = L"WindowClass";
static const wchar_t* s_PropName = L"WindowData";

static u64 s_ClockFrequency;
static u64 s_StartTime;

LRESULT CALLBACK _Win32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);