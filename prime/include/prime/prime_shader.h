#pragma once

#include "prime_defines.h"
#include "prime_math.h"

PRIME_API prime_Shader*
prime_ShaderCreate(prime_Device* device, const char* vertex_shader, const char* pixel_shader, b8 load = true);

PRIME_API void
prime_ShaderDestroy(prime_Shader* shader);

PRIME_API void
prime_ShaderBind(prime_Shader* shader);

PRIME_API void
prime_ShaderUnbind(prime_Shader* shader);

PRIME_API void
prime_ShaderSetInt(prime_Shader* shader, const char* name, i32 data);

PRIME_API void
prime_ShaderSetIntArray(prime_Shader* shader, const char* name, i32* data, u32 count);

PRIME_API void
prime_ShaderSetFloat(prime_Shader* shader, const char* name, f32 data);

PRIME_API void
prime_ShaderSetFloat2(prime_Shader* shader, const char* name, prime_Vec2 data);

PRIME_API void
prime_ShaderSetFloat3(prime_Shader* shader, const char* name, prime_Vec3 data);

PRIME_API void
prime_ShaderSetFloat4(prime_Shader* shader, const char* name, prime_Vec4 data);

PRIME_API void
prime_ShaderSetMat4(prime_Shader* shader, const char* name, prime_Mat4 data);