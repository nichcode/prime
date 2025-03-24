
#pragma once

#include "defines.h"

struct prime_window;
struct prime_context;

PRIME_API prime_context* prime_create_context(prime_window* window);
PRIME_API void prime_destroy_context(prime_context* context);

PRIME_API void prime_context_clear(prime_context* context);
PRIME_API void prime_context_present(prime_context* context);

PRIME_API void prime_context_set_vsync(prime_context* context, b8 vsync);
PRIME_API void prime_context_set_clearcolor(prime_context* context, f32 r, f32 g, f32 b, f32 a);
PRIME_API void prime_context_set_clearcolori(prime_context* context, u32 r, u32 g, u32 b, u32 a);

