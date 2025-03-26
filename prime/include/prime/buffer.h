
#pragma once

#include "defines.h"

struct primeBuffer;

using primeBufferType = u32; 
using primeBufferUsage = u32; 

enum primeBufferTypes_
{
    primeBufferTypes_Vertex,
    primeBufferTypes_Index,
    primeBufferTypes_Uniform,
    primeBufferTypes_Storage
};

enum primeBufferUsages_
{
    primeBufferUsages_Static,
    primeBufferUsages_Dynamic
};

struct primeBufferDesc
{
    primeBufferType type = primeBufferTypes_Vertex;
    primeBufferUsage usage = primeBufferUsages_Static;
    u32 size = 0;
    void* data = nullptr;
};

PRIME_API primeBuffer* primeCreateBuffer(primeBufferDesc desc);
PRIME_API void primeDestroyBuffer(primeBuffer* buffer);

PRIME_API void primeSetBufferData(primeBuffer* buffer, const void* data, u32 size);
PRIME_API void primeBindBuffer(primeBuffer* buffer);
PRIME_API void primeUnbindBuffer(primeBuffer* buffer);
