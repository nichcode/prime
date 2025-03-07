
#pragma once

#include "win32_API.h"

namespace prime::internal {

    void wglContextCreateDummy();
    HGLRC wglContextCreate(HWND window);
    void wglContextDestroy(HGLRC context);
   
    void wglContextMakeCurrent(HWND window, HGLRC context);
    void wglContextSetVsync(int interval);
    
} // namespace prime::internal
