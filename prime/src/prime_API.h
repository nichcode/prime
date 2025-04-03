
#pragma once

#include "prime/prime.h"

struct API
{
    // context
    void*(*createContext)(void* window_handle) = nullptr;
    void(*destroyContext)(void* handle) = nullptr;
    void(*swapBuffers)(void* handle) = nullptr;
    void(*setClearColor)(void* handle, prime_vec4 color) = nullptr;
    void(*setVsync)(void* handle, b8 vsync) = nullptr;
    void(*makeActive)(void* handle) = nullptr;
    void(*clear)(void* handle) = nullptr;
};

void prime_InitAPI();
void prime_ShutdownAPI();