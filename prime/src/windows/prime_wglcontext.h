#pragma once

#include "prime/prime_defines.h"

#ifdef PRIME_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

void 
wgl_ContextCreateDummy();

HGLRC 
wgl_ContextCreate(HWND window);

void 
wgl_ContextDestroy(HGLRC context);

void 
wgl_ContextMakeCurrent(HWND window, HGLRC context);

void 
wgl_ContextSetVsync(int interval);

#endif // PRIME_PLATFORM_WINDOWS