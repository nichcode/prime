
#pragma once

#include "defines.h"

struct prContext;
struct prBuffer;

enum prBufferTypes_
{
    prBufferTypes_Vertex,
    prBufferTypes_Index,
    prBufferTypes_Storage,
    prBufferTypes_Uniform
};

enum prBufferUsages_
{
    prBufferUsages_Static,
    prBufferUsages_Dynamic
};

struct prBufferDesc
{
    u32 type = 0;
    u32 usage = 0;
    u32 size = 0;
    u32 binding = 0;
    void* data = nullptr;
};

PR_API prBuffer* prCreateBuffer(prContext* context, prBufferDesc desc);
PR_API void prDestroyBuffer(prBuffer* buffer);

PR_API void prBindBuffer(prBuffer* buffer);
PR_API void prSetBufferData(u32 type, void* data, u32 size);
