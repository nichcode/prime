#pragma once

#include "prime_defines.h"

#ifdef PRIME_PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

PRIME_API HWND 
prime_WindowGetWin32Handle(prime_Window* window);

PRIME_API HINSTANCE 
prime_WindowGetWin32HInstance(prime_Window* window);

#endif // PRIME_PLATFORM_WINDOWS

