
#pragma once

#include "prime/context.h"

void* _glCreateContext(primeWindow* window);
void _glDestroyContext(void* context);

void _glClear(void* context);
void _glPresent(void* context);
void _glBindContext(void* context);
void _glUnbindContext(void* context);

void _glSubmit(void* context, primeDrawType type, primeDrawMode mode, u32 count);
void _glSubmitInstanced(void* context, primeDrawType type, primeDrawMode mode, u32 count, u32 ins_count);

void _glMakeActive(void* context);
void _glSetVsync(void* context, b8 vsync);
void _glSetBlendMode(void* context, primeBlendMode blend);

void _glSetClearColor(void* context, f32 r, f32 g, f32 b, f32 a);
void _glSetView(void* context, const primeView* view);