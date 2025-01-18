#pragma once

#include "pr_defines.h"

struct PrWindow;

#ifdef PR_PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

PR_API HWND 
prWin32GetWindowHandle(PrWindow* window);

PR_API HINSTANCE 
prWin32GetHInstance(PrWindow* window);

#endif // PR_PLATFORM_WINDOWS

