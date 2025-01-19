#pragma once

#include "prime/prime_color.h"
#include "prime/prime_context.h"

struct prime_ContextHandle;

#ifdef PRIME_PLATFORM_WINDOWS

prime_ContextHandle*
dx11_CreateContext(prime_Window* window);

void
dx11_GDestroy(prime_ContextHandle* context_handle);

void
dx11_Swapbuffer(prime_Window* window, prime_ContextHandle* context_handle);

void
dx11_SetClearColor(prime_ContextHandle* context_handle, const prime_Color& color);

void
dx11_Clear(prime_ContextHandle* context_handle);

void
dx11_MakeActive(prime_Window* window, prime_ContextHandle* context_handle);

void
dx11_SetVsync(prime_ContextHandle* context_handle, b8 vsync);

#endif // PRIME_PLATFORM_WINDOWS

