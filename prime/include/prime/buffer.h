
#pragma once

#include "defines.h"

struct primeBuffer;

enum primeBufferType
{
    PRIME_BUFFER_TYPE_VERTEX,
    PRIME_BUFFER_TYPE_INDEX,
    PRIME_BUFFER_TYPE_UNIFORM,
    PRIME_BUFFER_TYPE_STORAGE
};

enum primeBufferUsage
{
    PRIME_BUFFER_USAGE_STATIC,
    PRIME_BUFFER_USAGE_DYNAMIC
};

struct primeBufferDesc
{
    primeBufferType type = PRIME_BUFFER_TYPE_VERTEX;
    primeBufferUsage usage = PRIME_BUFFER_USAGE_DYNAMIC;
    u32 size = 0;
    void* data = nullptr;
};

PRIME_API primeBuffer* primeCreateBuffer(primeBufferDesc desc);
PRIME_API void primeDestroyBuffer(primeBuffer* buffer);

PRIME_API void primeSetBufferData(primeBuffer* buffer, const void* data, u32 size);
PRIME_API void primeBindBuffer(primeBuffer* buffer);
PRIME_API void primeUnbindBuffer(primeBuffer* buffer);
