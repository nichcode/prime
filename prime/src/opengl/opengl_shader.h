
#pragma once

#include "prime/prime.h"

void* gl_CreateShader(prime_shader_desc desc);
void gl_DestroyShader(void* handle);

void gl_SetInt(void* handle, const char* name, i32 data);
void gl_SetIntArray(void* handle, const char* name, i32* data, u32 count);
void gl_SetFloat(void* handle, const char* name, f32 data);
void gl_SetFloat2(void* handle, const char* name, prime_vec2 data);
void gl_SetFloat3(void* handle, const char* name, prime_vec3 data);
void gl_SetFloat4(void* handle, const char* name, prime_vec4 data);
void gl_SetMat4(void* handle, const char* name, prime_mat4 data);

void gl_BindShader(void* handle);
