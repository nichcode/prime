
#pragma once

#include "defines.h"

struct prContext;
struct prShader;

enum prShaderDataTypes_
{
    prShaderDataTypes_Int,
    prShaderDataTypes_Int2,
    prShaderDataTypes_Int3,
    prShaderDataTypes_Int4,
    prShaderDataTypes_Float,
    prShaderDataTypes_Float2,
    prShaderDataTypes_Float3,
    prShaderDataTypes_Float4
};

enum prShaderSourceTypes_
{
    prShaderSourceTypes_GLSL,
};

struct prShaderAttrib
{
    u32 divisor = 0;
    b8 normalize = false;
    u32 type = 0;
};

struct prShaderLayout
{
    prShaderAttrib attribs[PR_MAX_ATTRIB]{};
    u32 count = 0;
};

struct prShaderDesc
{
    u32 type = 0;
    const char* vertex_src = nullptr;
    const char* pixel_src = nullptr;
    b8 load = true;
    prShaderLayout layout;
};

PR_API prShader* prCreateShader(prShaderDesc desc);
PR_API void prDestroyShader(prShader* shader);
PR_API void prBindShader(prShader* shader);

PR_API void prSetInt(const char* name, i32 data);
PR_API void prSetIntArray(const char* name, i32* data, u32 count);
PR_API void prSetFloat(const char* name, f32 data);
PR_API void prSetFloat2(const char* name, f32 data, f32 data2);
PR_API void prSetFloat3(const char* name, f32 data, f32 data2, f32 data3);
PR_API void prSetFloat4(const char* name, f32 data, f32 data2, f32 data3, f32 data4);
PR_API void prSetMat4(const char* name, f32* data);
