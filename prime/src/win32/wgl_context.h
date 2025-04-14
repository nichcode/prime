
#pragma once

#include "win32_API.h"
#include "vendor/wglext.h"

static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = nullptr;

void _WGLCreateDummyContext();
HGLRC _WGLCreateContext(HWND window, i32 major, i32 minor);
