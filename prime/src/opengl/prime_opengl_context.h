#pragma once

#include "prime/prime_context.h"

struct prime_ContextHandle;

prime_ContextHandle*
gl_CreateContext(prime_Window* window);

void
gl_GDestroyContext(prime_ContextHandle* context_handle);

void
gl_Swapbuffer(prime_Window* window, prime_ContextHandle* context_handle);

void
gl_SetClearColor(prime_ContextHandle* context_handle, const prime_Color& color);

void
gl_Clear(prime_ContextHandle* context_handle);

void
gl_MakeActive(prime_Window* window, prime_ContextHandle* context_handle);

void
gl_SetVsync(prime_ContextHandle* context_handle, b8 vsync);

void
gl_SetViewport(prime_ContextHandle* context_handle, const prime_Viewport* viewport);

void
gl_DrawIndexed(prime_ContextHandle* context_handle, prime_Topology topology, u32 count);