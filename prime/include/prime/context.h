
#pragma once

#include "defines.h"
#include "prime/maths.h"

struct prime_window;
struct prime_context;

struct prime_view
{
    prime_ivec2 pos;
    prime_uvec2 size;
};

PRIME_API prime_context* prime_create_context(prime_window* window);
PRIME_API void prime_destroy_context(prime_context* context);

PRIME_API void prime_context_clear(prime_context* context);
PRIME_API void prime_context_present(prime_context* context);

PRIME_API void prime_context_set_vsync(prime_context* context, b8 vsync);
PRIME_API void prime_context_set_clearcolor(prime_context* context, const prime_vec4 color);
PRIME_API void prime_context_set_clearcolori(prime_context* context, const prime_uvec4 color);

PRIME_API void prime_context_setview(prime_context* context, const prime_view view);

PRIME_API const prime_view* prime_context_getview(prime_context* context);