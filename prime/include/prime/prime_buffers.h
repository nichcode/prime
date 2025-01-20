#pragma once

#include "prime_defines.h"

enum prime_DataType
{
    prime_DataTypeInt,
    prime_DataTypeInt2,
    prime_DataTypeInt3,
    prime_DataTypeInt4,
    prime_DataTypeFloat,
    prime_DataTypeFloat2,
    prime_DataTypeFloat3,
    prime_DataTypeFloat4,
    prime_DataTypeMat3,
    prime_DataTypeMat4,
    prime_DataTypeBool,
};

enum prime_VertexbufferType
{
    prime_VertexbufferTypeStatic,
    prime_VertexbufferTypeDynamic
};

struct prime_BufferElement
{
    prime_DataType type = prime_DataTypeFloat3;
    u32 size = 0;
    u64 offset = 0;
};

PRIME_INLINE u32
prime_DataTypeGetSize(prime_DataType type)
{
    switch (type)
    {
    case prime_DataTypeInt:
    case prime_DataTypeFloat: {
        return 4;
    }

    case prime_DataTypeInt2:
    case prime_DataTypeFloat2: {
        return 8;
    }

    case prime_DataTypeInt3:
    case prime_DataTypeFloat3: {
        return 12;
    }

    case prime_DataTypeInt4:
    case prime_DataTypeFloat4: {
        return 16;
    }

    case prime_DataTypeMat3:     return 4 * 3 * 3;
    case prime_DataTypeMat4:     return 4 * 4 * 4;
    case prime_DataTypeBool:     return 1;
    }
    return 0;
}

PRIME_INLINE u32
prime_DataTypeGetCount(prime_DataType type)
{
    switch (type)
    {
    case prime_DataTypeFloat:
    case prime_DataTypeInt:
    case prime_DataTypeBool: {
        return 1;
    }

    case prime_DataTypeFloat2:
    case prime_DataTypeInt2: {
        return 2;
    }

    case prime_DataTypeFloat3:
    case prime_DataTypeInt3: {
        return 3;
    }

    case prime_DataTypeFloat4:
    case prime_DataTypeInt4: {
        return 4;
    }


    case prime_DataTypeMat3:     return 9;
    case prime_DataTypeMat4:     return 16;
    }
    return 0;
}

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

PRIME_INLINE prime_BufferElement
prime_BufferElementCreate(prime_DataType type)
{
    prime_BufferElement element;
    element.type = type;
    element.size = prime_DataTypeGetSize(type);
    return element;
}