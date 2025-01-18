#pragma once

#include "prime/pr_defines.h"

#ifdef PR_PLATFORM_WINDOWS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

void 
prWGLContextCreateDummy();

HGLRC 
prWGLContextCreate(HWND window);

void 
prWGLContextDestroy(HGLRC context);

void 
prWGLContextMakeCurrent(HWND window, HGLRC context);

void 
prWGLContextSetVsync(int interval);

#endif // PR_PLATFORM_WINDOWS