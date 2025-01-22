#pragma once

#include "prime_defines.h"

PRIME_API prime_Context*
prime_ContextCreate(prime_Device* device, prime_Window* window);

PRIME_API void
prime_ContextDestroy(prime_Context* device);

PRIME_API void
prime_ContextSwapbuffers(prime_Context* context);

PRIME_API void
prime_ContextSetClearColor(prime_Context* context, const prime_Color& color);

PRIME_API void
prime_ContextClear(prime_Context* context);

PRIME_API void
prime_ContextMakeActive(prime_Context* context);

PRIME_API void
prime_ContextSetVsync(prime_Context* context, b8 vsync);

PRIME_API void
prime_ContextSetAntiAliasing(prime_Context* context, b8 anti_aliasing);

PRIME_API void
prime_ContextSetLinesWidth(prime_Context* context, f32 width);

PRIME_API void
prime_ContextSetViewport(prime_Context* context, const prime_Viewport* viewport);

PRIME_API prime_Viewport
prime_ContextGetViewport(prime_Context* context);

PRIME_API b8
prime_ContextGetVSync(prime_Context* context);

PRIME_API b8
prime_ContextGetAntiAliasing(prime_Context* context);

PRIME_API f32
prime_ContextGetLinesWidth(prime_Context* context);

PRIME_API void
prime_ContextDrawIndexed(prime_Context* context, prime_DrawMode draw_mode, u32 count);