
#pragma once

#include "defines.h"
#include "prime/maths.h"

struct prime_view
{
    prime_ivec2 pos;
    prime_uvec2 size;
};

struct prime_window;
struct prime_context;
struct prime_buffer;
struct prime_shader;
struct prime_layout;

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

enum prime_shader_source_type
{
    PRIME_SHADER_SOURCE_TYPE_GLSL
};

enum prime_data_type
{
    PRIME_DATA_TYPE_INT,
    PRIME_DATA_TYPE_INT2,
    PRIME_DATA_TYPE_INT3,
    PRIME_DATA_TYPE_INT4,
    PRIME_DATA_TYPE_FLOAT,
    PRIME_DATA_TYPE_FLOAT2,
    PRIME_DATA_TYPE_FLOAT3,
    PRIME_DATA_TYPE_FLOAT4,
    PRIME_DATA_TYPE_BOOL
};

enum prime_draw_mode
{
    PRIME_DRAW_MODE_TRIANGLES,
    PRIME_DRAW_MODE_LINES
};

enum prime_draw_type
{
    PRIME_DRAW_TYPE_ARRAYS,
    PRIME_DRAW_TYPE_ELEMENTS
};

struct prime_buffer_desc
{
    prime_buffer_type type = PRIME_BUFFER_TYPE_VERTEX;
    prime_buffer_usage usage = PRIME_BUFFER_USAGE_DYNAMIC;
    u32 size = 0;
    void* data = nullptr;
};

struct prime_shader_desc
{
    prime_shader_source_type source_type = PRIME_SHADER_SOURCE_TYPE_GLSL;
    const char* vertex_src = nullptr;
    const char* pixel_src = nullptr;
    b8 load = true;
};

PRIME_API prime_context* prime_create_context(prime_window* window);
PRIME_API void prime_destroy_context(prime_context* context);

PRIME_API void prime_context_clear(prime_context* context);
PRIME_API void prime_context_present(prime_context* context);
PRIME_API void prime_context_submit(prime_context* context, prime_draw_type type, prime_draw_mode mode, u32 count);

PRIME_API void prime_context_set_vsync(prime_context* context, b8 vsync);
PRIME_API void prime_context_set_clearcolor(prime_context* context, const prime_vec4 color);
PRIME_API void prime_context_set_clearcolori(prime_context* context, const prime_uvec4 color);

PRIME_API void prime_context_setview(prime_context* context, const prime_view view);
PRIME_API const prime_view* prime_context_getview(prime_context* context);

PRIME_API prime_buffer* prime_create_buffer(prime_context* context, prime_buffer_desc desc);
PRIME_API void prime_destroy_buffer(prime_buffer* buffer);

PRIME_API prime_shader* prime_create_shader(prime_context* context, prime_shader_desc desc);
PRIME_API void prime_destroy_shader(prime_shader* shader);

PRIME_API prime_layout* prime_create_layout(prime_context* context);
PRIME_API void prime_destroy_layout(prime_layout* layout);

PRIME_API void prime_set_buffer_data(prime_buffer* buffer, const void* data, u32 size);
PRIME_API void prime_add_attrib(prime_layout* layout, prime_data_type type, u32 divisor, b8 normalize);

PRIME_API void prime_set_shader_int(prime_shader* shader, const char* name, i32 data);
PRIME_API void prime_set_shader_int_array(prime_shader* shader, const char* name, i32* data, u32 count);
PRIME_API void prime_set_shader_float(prime_shader* shader, const char* name, f32 data);
PRIME_API void prime_set_shader_float2(prime_shader* shader, const char* name, prime_vec2 data);
PRIME_API void prime_set_shader_float3(prime_shader* shader, const char* name, prime_vec3 data);
PRIME_API void prime_set_shader_float4(prime_shader* shader, const char* name, prime_vec4 data);
PRIME_API void prime_set_shader_mat2(prime_shader* shader, const char* name, prime_mat2 data);
PRIME_API void prime_set_shader_mat3(prime_shader* shader, const char* name, prime_mat3 data);
PRIME_API void prime_set_shader_mat4(prime_shader* shader, const char* name, prime_mat4 data);

PRIME_API void prime_set_buffer(prime_buffer* buffer);
PRIME_API void prime_set_shader(prime_shader* shader);
PRIME_API void prime_set_layout(prime_layout* layout);