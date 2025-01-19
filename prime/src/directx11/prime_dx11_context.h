#pragma once

#include "prime/prime_color.h"

struct prime_Window;
struct prime_ContextHandle;

#ifdef PRIME_PLATFORM_WINDOWS

prime_ContextHandle*
prime_Dx11CreateContext(prime_Window* window);

void
prime_Dx11GDestroy(prime_ContextHandle* context_handle);

void
prime_Dx11Swapbuffer(prime_Window* window, prime_ContextHandle* context_handle);

void
prime_Dx11SetClearColor(prime_ContextHandle* context_handle, const prime_Color& color);

void
prime_Dx11Clear(prime_ContextHandle* context_handle);

void
prime_Dx11MakeActive(prime_Window* window, prime_ContextHandle* context_handle);

void
prime_Dx11SetVsync(prime_ContextHandle* context_handle, b8 vsync);

#endif // PRIME_PLATFORM_WINDOWS

