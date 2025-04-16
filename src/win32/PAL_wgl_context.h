
#pragma once

#include "PAL_win32_API.h"
#include "wglext.h"

static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = nullptr;

void _WGLCreateDummyContext();
HGLRC _WGLCreateContext(HWND window, i32 major, i32 minor);
