#pragma once

#include "prime/prime_defines.h"

#ifdef PRIME_PLATFORM_WINDOWS

void*
dx11_ContextCreate(prime_Window* window);

void
dx11_ContextDestroy(void* handle);

void
dx11_ContextSwapbuffer(prime_Window* window, void* handle);

void
dx11_ContextSetClearColor(void* handle, const prime_Color& color);

void
dx11_ContextClear(void* handle);

void
dx11_ContextMakeActive(prime_Window* window, void* handle);

void
dx11_ContextSetVsync(void* handle, b8 vsync);

#endif // PRIME_PLATFORM_WINDOWS

