
#pragma once

#include "windows_API.h"

void wgl_CreateDummyContext();

HGLRC wgl_CreateContext(HWND window);
void wgl_DestroyContext(HGLRC context);

void wgl_MakeActive(HDC deviceContext, HGLRC context);
void wgl_SetSetVsync(int interval);


