
#pragma once

#include "prime/context.h"

void* gl_create_context(prime_window* window);
void gl_destroy_context(void* context);

void gl_context_clear(void* context);
void gl_context_present(void* context);

void gl_context_make_active(void* context);
void gl_context_set_vsync(void* context, b8 vsync);
void gl_context_set_clearcolor(void* context, f32 r, f32 g, f32 b, f32 a);
