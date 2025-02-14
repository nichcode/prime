#pragma once

#include "prime/prime_context.h"

void*
primeGLContextCreate(primeWindow* window);

void
primeGLContextDestroy(void* handle);

void
primeGLContextSwapbuffer(primeWindow* window, void* handle);

void
primeGLContextSetClearColor(void* handle, primeColor* color);

void
primeGLContextSetAntiAliasing(void* context, b8 anti_aliasing);

void
primeGLContextSetLinesWidth(void* context, f32 width);

void
primeGLContextClear(void* handle);

void
primeGLContextMakeActive(primeWindow* window, void* handle);

void
primeGLContextSetVsync(void* handle, b8 vsync);

void
primeGLContextSetViewport(void* handle, primeViewport* viewport);

void
primeGLContextDrawArrays(void* handle, primeDrawMode draw_mode, u32 count);

void
primeGLContextDrawElements(void* handle, primeDrawMode draw_mode, u32 count);

void
primeGLContextDrawElementsInstanced(void* handle, primeDrawMode draw_mode, u32 count, u32 instance_count);