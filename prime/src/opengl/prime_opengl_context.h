#pragma once

#include "prime/prime_defines.h"

void*
gl_ContextCreate(prime_Window* window);

void
gl_ContextDestroy(void* handle);

void
gl_ContextSwapbuffer(prime_Window* window, void* handle);

void
gl_ContextSetClearColor(void* handle, const prime_Color& color);

void
gl_ContextSetAntiAliasing(void* context, b8 anti_aliasing);

void
gl_ContextSetLinesWidth(void* context, f32 width);

void
gl_ContextClear(void* handle);

void
gl_ContextMakeActive(prime_Window* window, void* handle);

void
gl_ContextSetVsync(void* handle, b8 vsync);

void
gl_ContextSetViewport(void* handle, const prime_Viewport* viewport);

void
gl_ContextDrawIndexed(void* handle, prime_DrawMode draw_mode, u32 count);