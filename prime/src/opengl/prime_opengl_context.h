#pragma once

#include "prime/prime_color.h"

struct prime_Window;
struct prime_ContextHandle;

prime_ContextHandle*
prime_GLCreateContext(prime_Window* window);

void
prime_GLGDestroy(prime_ContextHandle* context_handle);

void
prime_GLSwapbuffer(prime_Window* window, prime_ContextHandle* context_handle);

void
prime_GLSetClearColor(prime_ContextHandle* context_handle, const prime_Color& color);

void
prime_GLClear(prime_ContextHandle* context_handle);

void
prime_GLMakeActive(prime_Window* window, prime_ContextHandle* context_handle);

void
prime_GLSetVsync(prime_ContextHandle* context_handle, b8 vsync);