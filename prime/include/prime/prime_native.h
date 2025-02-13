#pragma once

#include "prime_defines.h"

#ifdef PPLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

PAPI HWND
primeWindowGetWin32Handle(primeWindow* window);

PAPI HINSTANCE
primeWindowGetWin32HInstance(primeWindow* window);

#endif // PPLATFORM_WINDOWS