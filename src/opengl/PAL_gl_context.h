
#pragma once

#include "PAL/PAL_context.h"

void* _GLCreateContext(void* window_handle, i32 major, i32 minor);
void _GLDestroyContext(void* handle);

void _GLSwapBuffers(void* handle);
void _GLClear(void* handle, const PAL_Color color);
void _GLMakeActive(void* handle);

void _GLSetVsync(void* handle, b8 vsync);
void _GLSetBlendMode(void* handle, u32 blend_mode);

void _GLDrawArrays(void* handle, u32 mode, u32 count);
void _GLDrawElements(void* handle, u32 mode, u32 count);
void _GLDrawArraysInstanced(void* handle, u32 mode, u32 count, u32 instance_count);
void _GLDrawElementsInstanced(void* handle, u32 mode, u32 count, u32 instance_count);

void _GLSetView(void* handle, PAL_Viewport view);