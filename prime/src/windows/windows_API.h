
#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>

static HINSTANCE s_Instance;
static WINDOWPLACEMENT s_WndPlacement;

static const wchar_t* s_ClassName = L"WindowClass";
static const wchar_t* s_PropName = L"WindowData";

LRESULT CALLBACK windowsProc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

void windows_PlatformInit();
void windows_PlatformShutdown();