
#pragma once

#include "defines.h"
#include "prime/maths.h"

struct prime_window;
struct prime_context;

enum prime_buffer_type
{
    PRIME_BUFFER_TYPE_VERTEX,
    PRIME_BUFFER_TYPE_INDEX,
    PRIME_BUFFER_TYPE_UNIFORM,
    PRIME_BUFFER_TYPE_STORAGE
};

enum prime_buffer_usage
{
    PRIME_BUFFER_USAGE_STATIC,
    PRIME_BUFFER_USAGE_DYNAMIC
};

struct prime_buffer_desc
{
    prime_buffer_type type = PRIME_BUFFER_TYPE_VERTEX;
    prime_buffer_usage usage = PRIME_BUFFER_USAGE_DYNAMIC;
    u32 size = 0;
    void* data = nullptr;
};

struct prime_buffer;

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

PRIME_API prime_buffer* prime_create_buffer(prime_context* context, prime_buffer_desc desc);
PRIME_API void prime_destroy_buffer(prime_buffer* buffer);

PRIME_API void prime_set_buffer(prime_buffer* buffer);
PRIME_API void prime_set_buffer_data(prime_buffer* buffer, const void* data, u32 size);