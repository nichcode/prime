#pragma once

#include "prime_defines.h"
#include "prime_log.h"

struct prime_Device;
struct prime_Vertexbuffer;
struct prime_Indexbuffer;
struct prime_BufferLayout;

enum prime_BufferDataType
{
    prime_BufferDataTypeNone,
    prime_BufferDataTypeInt,
    prime_BufferDataTypeInt2,
    prime_BufferDataTypeInt3,
    prime_BufferDataTypeInt4,
    prime_BufferDataTypeFloat,
    prime_BufferDataTypeFloat2,
    prime_BufferDataTypeFloat3,
    prime_BufferDataTypeFloat4,
    prime_BufferDataTypeMat3,
    prime_BufferDataTypeMat4,
    prime_BufferDataTypeBool,
};

enum prime_VertexbufferType
{
    prime_VertexbufferTypeStatic,
    prime_VertexbufferTypeDynamic
};

struct prime_BufferElement
{
    prime_BufferDataType type = prime_BufferDataTypeNone;
    u32 size = 0;
    u64 offset = 0;
};

PRIME_INLINE u32
prime_GetDataTypeSize(prime_BufferDataType type)
{
    switch (type)
    {
    case prime_BufferDataTypeInt:
    case prime_BufferDataTypeFloat: {
        return 4;
    }

    case prime_BufferDataTypeInt2:
    case prime_BufferDataTypeFloat2: {
        return 8;
    }

    case prime_BufferDataTypeInt3:
    case prime_BufferDataTypeFloat3: {
        return 12;
    }

    case prime_BufferDataTypeInt4:
    case prime_BufferDataTypeFloat4: {
        return 16;
    }

    case prime_BufferDataTypeMat3:     return 4 * 3 * 3;
    case prime_BufferDataTypeMat4:     return 4 * 4 * 4;
    case prime_BufferDataTypeBool:     return 1;
    }

    PRIME_ASSERT_MSG(false, "Invalid prime_BufferDataType");
    return 0;
}

PRIME_INLINE u32
prime_GetDataTypeCount(prime_BufferDataType type)
{
    switch (type)
    {
    case prime_BufferDataTypeFloat:
    case prime_BufferDataTypeInt:
    case prime_BufferDataTypeBool: {
        return 1;
    }

    case prime_BufferDataTypeFloat2:
    case prime_BufferDataTypeInt2: {
        return 2;
    }

    case prime_BufferDataTypeFloat3:
    case prime_BufferDataTypeInt3: {
        return 3;
    }

    case prime_BufferDataTypeFloat4:
    case prime_BufferDataTypeInt4: {
        return 4;
    }


    case prime_BufferDataTypeMat3:     return 9;
    case prime_BufferDataTypeMat4:     return 16;
    }

    PRIME_ASSERT_MSG(false, "Invalid prime_BufferDataType");
    return 0;
}

PRIME_API prime_BufferLayout*
prime_CreateBufferLayout();

PRIME_API void
prime_DestroyBufferLayout(prime_BufferLayout* layout);

PRIME_API void
prime_AddBufferElement(prime_BufferLayout* layout, const prime_BufferElement& element);

PRIME_API prime_Vertexbuffer*
prime_CreateVertexbuffer(prime_Device* device, const void* data,
    u32 size, prime_VertexbufferType type);

PRIME_API void
prime_DestroyVertexbuffer(prime_Vertexbuffer* vertexbuffer);

PRIME_API void
prime_SetBufferLayout(prime_Vertexbuffer* vertexbuffer, prime_BufferLayout* layout);

PRIME_API void
prime_BindVertexbuffer(prime_Vertexbuffer* vertexbuffer);

PRIME_API void
prime_UnbindVertexbuffer(prime_Vertexbuffer* vertexbuffer);

PRIME_API prime_VertexbufferType
prime_GetVertexbufferType(prime_Vertexbuffer* vertexbuffer);

PRIME_API prime_BufferLayout*
prime_GetBufferLayout(prime_Vertexbuffer* vertexbuffer);

PRIME_API void
prime_SetVertexbufferData(prime_Vertexbuffer* vertexbuffer,
    const void* data, u32 size);

PRIME_API prime_Indexbuffer*
prime_CreateIndexbuffer(prime_Device* device, u32* indices, u32 count);

PRIME_API void
prime_DestroyIndexbuffer(prime_Indexbuffer* indexbuffer);

PRIME_API void
prime_BindIndexbuffer(prime_Indexbuffer* indexbuffer);

PRIME_API void
prime_UnbindIndexbuffer(prime_Indexbuffer* indexbuffer);

PRIME_API u32
prime_GetIndexbufferCount(prime_Indexbuffer* indexbuffer);

PRIME_INLINE prime_BufferElement
prime_CreateBufferElement(prime_BufferDataType type)
{
    prime_BufferElement element;
    element.type = type;
    element.size = prime_GetDataTypeSize(type);
    return element;
}