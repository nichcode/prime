#pragma once

#include "prime/prime_defines.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

void 
primeWGLContextCreateDummy();

HGLRC 
primeWGLContextCreate(HWND window);

void 
primeWGLContextDestroy(HGLRC context);

void 
primeWGLContextMakeCurrent(HWND window, HGLRC context);

void 
primeWGLContextSetVsync(int interval);