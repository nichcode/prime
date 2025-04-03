
#pragma once

#include "windows_API.h"

namespace prime {

    void wglCreateDummyContext();

    HGLRC wglCreateContext(HWND window);
    void wglDestroyContext(HGLRC context);

    void wglMakeActive(HDC deviceContext, HGLRC context);
    void wglSetSetVsync(int interval);
    
} // namespace prime


