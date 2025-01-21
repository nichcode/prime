#pragma once

#include "prime_defines.h"

PRIME_API prime_BufferLayout*
prime_BufferLayoutCreate();

PRIME_API void
prime_BufferLayoutDestroy(prime_BufferLayout* layout);

PRIME_API void
prime_BufferElementAdd(prime_BufferLayout* layout, const prime_BufferElement& element);

PRIME_API prime_Vertexbuffer*
prime_VertexbufferCreate(prime_Device* device, const void* data,
    u32 size, prime_VertexbufferType type);

PRIME_API void
prime_VertexbufferDestroy(prime_Vertexbuffer* vertexbuffer);

PRIME_API void
prime_BufferLayoutSet(prime_Vertexbuffer* vertexbuffer, prime_BufferLayout* layout);

PRIME_API void
prime_VertexbufferBind(prime_Vertexbuffer* vertexbuffer);

PRIME_API void
prime_VertexbufferUnbind(prime_Vertexbuffer* vertexbuffer);

PRIME_API prime_VertexbufferType
prime_VertexbufferGetType(prime_Vertexbuffer* vertexbuffer);

PRIME_API prime_BufferLayout*
prime_BufferLayoutGet(prime_Vertexbuffer* vertexbuffer);

PRIME_API void
prime_VertexbufferSetData(prime_Vertexbuffer* vertexbuffer,
    const void* data, u32 size);

PRIME_API prime_Indexbuffer*
prime_IndexbufferCreate(prime_Device* device, u32* indices, u32 count);

PRIME_API void
prime_IndexbufferDestroy(prime_Indexbuffer* indexbuffer);

PRIME_API void
prime_IndexbufferBind(prime_Indexbuffer* indexbuffer);

PRIME_API void
prime_IndexbufferUnbind(prime_Indexbuffer* indexbuffer);

PRIME_API u32
prime_IndexbufferGetCount(prime_Indexbuffer* indexbuffer);

PRIME_API prime_Uniformbuffer*
prime_UniformbufferCreate(prime_Device* device, u32 size, u32 binding);

PRIME_API void
prime_UniformbufferDestroy(prime_Uniformbuffer* uniformbuffer);

PRIME_API void
prime_UniformbufferBind(prime_Uniformbuffer* uniformbuffer);

PRIME_API void
prime_UniformbufferUnbind(prime_Uniformbuffer* uniformbuffer);

PRIME_API void
prime_UniformbufferSetData(prime_Uniformbuffer* uniformbuffer, const void* data, u32 size);