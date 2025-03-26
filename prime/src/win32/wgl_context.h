
#pragma once

#include "pch.h"
#include "vendor/wglext.h"

void createDummyWGLContext();

HGLRC createWGLContext(HWND window);
void destroyWGLContext(HGLRC context);

void bindWGLContextCurrent(HDC deviceContext, HGLRC context);
void unbindWGLContextCurrent(HDC deviceContext, HGLRC context);
void setWGLContextVsync(int interval);