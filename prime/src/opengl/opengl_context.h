
#pragma once

#include "prime/context.h"

void* gl_create_context(prime_window* window);
void gl_destroy_context(void* context);

void gl_context_clear(void* context);
void gl_context_present(void* context);

void gl_context_make_active(void* context);
void gl_context_set_vsync(void* context, b8 vsync);
void gl_context_set_clearcolor(void* context, f32 r, f32 g, f32 b, f32 a);

void gl_context_set_clearcolor(void* context, const prime_view* view);

void* gl_create_buffer(prime_buffer_desc desc);
void gl_destroy_buffer(void* buffer);

void* gl_create_shader(prime_shader_desc desc);
void gl_destroy_shader(void* shader);

void gl_set_buffer_data(void* buffer, const void* data, u32 size);
void gl_set_shader_int(void* shader, const char* name, i32 data);
void gl_set_shader_int_array(void* shader, const char* name, i32* data, u32 count);
void gl_set_shader_float(void* shader, const char* name, f32 data);
void gl_set_shader_float2(void* shader, const char* name, prime_vec2 data);
void gl_set_shader_float3(void* shader, const char* name, prime_vec3 data);
void gl_set_shader_float4(void* shader, const char* name, prime_vec4 data);
void gl_set_shader_mat2(void* shader, const char* name, prime_mat2 data);
void gl_set_shader_mat3(void* shader, const char* name, prime_mat3 data);
void gl_set_shader_mat4(void* shader, const char* name, prime_mat4 data);

void gl_set_buffer(void* buffer);
void gl_set_shader(void* shader);