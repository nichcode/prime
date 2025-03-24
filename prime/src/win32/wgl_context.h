
#pragma once

#include "pch.h"
#include "vendor/wglext.h"

void createDummyWGLContext();

HGLRC createWGLContext(HWND window);
void destroyWGLContext(HGLRC context);

void makeWGLContextCurrent(HWND window, HGLRC context);
void setWGLContextVsync(int interval);