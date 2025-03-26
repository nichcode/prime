
#pragma once

#include "defines.h"
#include "prime/maths.h"

struct primeShader;

enum primeShaderSourceType
{
    PRIME_SHADER_SOURCE_TYPE_GLSL
};

struct primeShaderDesc
{
    primeShaderSourceType source_type = PRIME_SHADER_SOURCE_TYPE_GLSL;
    const char* vertex_src = nullptr;
    const char* pixel_src = nullptr;
    b8 load = true;
};

PRIME_API primeShader* primeCreateShader(primeShaderDesc desc);
PRIME_API void primeDestroyShader(primeShader* shader);

PRIME_API void primeSetInt(primeShader* shader, const char* name, i32 data);
PRIME_API void primeSetIntArray(primeShader* shader, const char* name, i32* data, u32 count);
PRIME_API void primeSetFloat(primeShader* shader, const char* name, f32 data);
PRIME_API void primeSetFloat2(primeShader* shader, const char* name, primeVec2 data);
PRIME_API void primeSetFloat3(primeShader* shader, const char* name, primeVec3 data);
PRIME_API void primeSetFloat4(primeShader* shader, const char* name, primeVec4 data);
PRIME_API void primeSetMat2(primeShader* shader, const char* name, primeMat2 data);
PRIME_API void primeSetMat3(primeShader* shader, const char* name, primeMat3 data);
PRIME_API void primeSetMat4(primeShader* shader, const char* name, primeMat4 data);

PRIME_API void primeBindShader(primeShader* shader);
PRIME_API void primeUnbindShader(primeShader* shader);