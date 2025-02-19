#pragma once

#include "prime_defines.h"
#include "prime_color.h"
#include "prime_viewport.h"

enum primeDrawMode
{
	primeDrawModeTriangles,
	primeDrawModeLines
};

PAPI primeContext*
primeContextCreate(primeDevice* device, primeWindow* window);

PAPI void
primeContextDestroy(primeContext* device);

PAPI void
primeContextSwapbuffers(primeContext* context);

PAPI void
primeContextSetClearColor(primeContext* context, primeColor* color);

PAPI void
primeContextClear(primeContext* context);

PAPI void
primeContextMakeActive(primeContext* context);

PAPI void
primeContextSetVsync(primeContext* context, b8 vsync);

PAPI void
primeContextSetAntiAliasing(primeContext* context, b8 anti_aliasing);

PAPI void
primeContextSetLinesWidth(primeContext* context, f32 width);

PAPI void
primeContextSetViewport(primeContext* context, primeViewport* viewport);

PAPI primeViewport
primeContextGetViewport(primeContext* context);

PAPI b8
primeContextGetVSync(primeContext* context);

PAPI b8
primeContextGetAntiAliasing(primeContext* context);

PAPI f32
primeContextGetLinesWidth(primeContext* context);

PAPI void
primeContextDrawArrays(primeContext* context, primeDrawMode draw_mode, u32 count);

PAPI void
primeContextDrawArraysInstanced(primeContext* context, primeDrawMode draw_mode, u32 count, u32 instance_count);

PAPI void
primeContextDrawElements(primeContext* context, primeDrawMode draw_mode, u32 count);

PAPI void
primeContextDrawElementsInstanced(primeContext* context, primeDrawMode draw_mode, u32 index_count, u32 instance_count);