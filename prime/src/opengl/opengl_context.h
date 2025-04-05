
#pragma once

#include "prime/prime.h"

void* gl_CreateContext(void* window_handle);
void gl_DestroyContext(void* handle);

void gl_SwapBuffers(void* handle);
void gl_Clear(void* handle);
void gl_MakeActive(void* handle);

void gl_SetVsync(void* handle, b8 vsync);
void gl_SetClearColor(void* handle, prime_vec4 color);
void gl_SetView(void* handle, prime_view view);

void gl_SubmitArrays(void* handle, u32 mode, u32 count);
void gl_SubmitElements(void* handle, u32 mode, u32 count);
void gl_SubmitLayout(void* handle, prime_layout* layout);

void gl_SubmitArraysInstanced(void* handle, u32 mode, u32 count, u32 instance_count);
void gl_SubmitElementsInstanced(void* handle, u32 mode, u32 count, u32 instance_count);