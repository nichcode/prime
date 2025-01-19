#pragma once

#include "prime_color.h"
#include "prime_viewport.h"

struct prime_Device;
struct prime_Context;
struct prime_Window;

enum prime_Topology
{
	prime_TopologyTriangles,
	prime_TopologyLines
};

PRIME_API prime_Context*
prime_CreateContext(prime_Device* device, prime_Window* window);

PRIME_API void
prime_DestroyContext(prime_Context* device);

PRIME_API void
prime_Swapbuffers(prime_Context* context);

PRIME_API void
prime_SetClearColor(prime_Context* context, const prime_Color& color);

PRIME_API void
prime_Clear(prime_Context* context);

PRIME_API void
prime_MakeActive(prime_Context* context);

PRIME_API void
prime_SetVsync(prime_Context* context, b8 vsync);

PRIME_API void
prime_SetViewport(prime_Context* context, const prime_Viewport* viewport);

PRIME_API prime_Viewport
prime_GetViewport(prime_Context* context);

PRIME_API void
prime_DrawIndexed(prime_Context* context, prime_Topology topology, u32 count);