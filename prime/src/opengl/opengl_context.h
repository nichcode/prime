
#pragma once

#include "prime/prime.h"

void* gl_CreateContext(void* window_handle);
void gl_DestroyContext(void* handle);

void gl_SwapBuffers(void* handle);
void gl_Clear(void* handle);
void gl_MakeActive(void* handle);

void gl_SetVsync(void* handle, b8 vsync);
void gl_SetClearColor(void* handle, prime_vec4 color);