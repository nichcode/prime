#pragma once

#include "prime/prime_defines.h"
#include "prime/prime_math.h"

void*
gl_ShaderCreate(const char* vertex_shader, const char* pixel_shader, b8 load);

void
gl_ShaderDestroy(void* shader);

void
gl_ShaderBind(void* shader);

void
gl_ShaderUnbind(void* shader);

void
gl_ShaderSetInt(void* shader, const char* name, i32 data);

void
gl_ShaderSetIntArray(void* shader, const char* name, i32* data, u32 count);

void
gl_ShaderSetFloat(void* shader, const char* name, f32 data);

void
gl_ShaderSetFloat2(void* shader, const char* name, prime_Vec2 data);

void
gl_ShaderSetFloat3(void* shader, const char* name, prime_Vec3 data);

void
gl_ShaderSetFloat4(void* shader, const char* name, prime_Vec4 data);

void
gl_ShaderSetMat4(void* shader, const char* name, prime_Mat4 data);