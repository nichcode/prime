#pragma once

#include "windows_API.h"

namespace prime {

    void 
    wglContextCreateDummy();

    HGLRC 
    wglContextCreate(HWND window);

    void 
    wglContextDestroy(HGLRC context);

    void 
    wglContextMakeCurrent(HWND window, HGLRC context);

    void 
    wglContextSetVsync(int interval);
    
} // namespace prime