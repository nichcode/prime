#pragma once

#include "prime_defines.h"

struct prime_Window;

#ifdef PRIME_PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

PRIME_API HWND 
prime_GetWin32WindowHandle(prime_Window* window);

PRIME_API HINSTANCE 
prime_GetWin32HInstance(prime_Window* window);

#endif // PRIME_PLATFORM_WINDOWS

