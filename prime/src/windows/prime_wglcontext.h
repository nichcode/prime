#pragma once

#include "prime/prime_defines.h"

#ifdef PRIME_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

void 
prime_WGLContextCreateDummy();

HGLRC 
prime_WGLContextCreate(HWND window);

void 
prime_WGLContextDestroy(HGLRC context);

void 
prime_WGLContextMakeCurrent(HWND window, HGLRC context);

void 
prime_WGLContextSetVsync(int interval);

#endif // PRIME_PLATFORM_WINDOWS