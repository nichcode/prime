
#include "opengl_layout.h"
#include "pch.h"
#include "opengl_funcs.h"

PRIME_INLINE u32 getDataTypeSize(primeDataType type)
{
    switch (type)
    {
        case PRIME_DATA_TYPE_INT:
        case PRIME_DATA_TYPE_FLOAT: {
            return 4;
        }

        case PRIME_DATA_TYPE_INT2:
        case PRIME_DATA_TYPE_FLOAT2: {
            return 8;
        }

        case PRIME_DATA_TYPE_INT3:
        case PRIME_DATA_TYPE_FLOAT3: {
            return 12;
        }

        case PRIME_DATA_TYPE_INT4:
        case PRIME_DATA_TYPE_FLOAT4: {
            return 16;
        }
        case PRIME_DATA_TYPE_BOOL:     return 1;
    }
    return 0;
}

PRIME_INLINE u32 getDataTypeCount(primeDataType type)
{
    switch (type)
    {
        case PRIME_DATA_TYPE_FLOAT:
        case PRIME_DATA_TYPE_INT:
        case PRIME_DATA_TYPE_BOOL: {
            return 1;
        }

        case PRIME_DATA_TYPE_FLOAT2:
        case PRIME_DATA_TYPE_INT2: {
            return 2;
        }

        case PRIME_DATA_TYPE_FLOAT3:
        case PRIME_DATA_TYPE_INT3: {
            return 3;
        }

        case PRIME_DATA_TYPE_FLOAT4:
        case PRIME_DATA_TYPE_INT4: {
            return 4;
        }
    }
    return 0;
}

PRIME_INLINE GLenum typeToGLType(primeDataType type)
{
    switch (type)
    {
        case PRIME_DATA_TYPE_INT:
        case PRIME_DATA_TYPE_INT2:
        case PRIME_DATA_TYPE_INT3:
        case PRIME_DATA_TYPE_INT4:
            return GL_INT;

        case PRIME_DATA_TYPE_FLOAT:
        case PRIME_DATA_TYPE_FLOAT2:
        case PRIME_DATA_TYPE_FLOAT3:
        case PRIME_DATA_TYPE_FLOAT4:
            return GL_FLOAT;

        case PRIME_DATA_TYPE_BOOL:
            return GL_BOOL;
    }
    return 0;
}

struct Element
{
    primeDataType type = PRIME_DATA_TYPE_FLOAT3;
    b8 normalize = false;
    u64 offset = 0;
    u32 size = 0;
    u32 divisor = 0;
};

struct glLayout
{
    u32 stride = 0;
    std::vector<Element> elements;
};

void* _glCreateLayout()
{
    glLayout* layout = new glLayout();
    return layout;
}

void _glDestroyLayout(void* handle)
{
    glLayout* layout = (glLayout*)handle;
    delete layout;
    layout = nullptr;
    layout = nullptr;
}

void _glAddAttrib(void* handle, primeDataType type, u32 divisor, b8 normalize)
{
    glLayout* layout = (glLayout*)handle;
    Element element;
    element.divisor = divisor;
    element.normalize = normalize;
    element.type = type;
    element.size = getDataTypeSize(type);
    layout->elements.push_back(element);
}

void _glBindLayout(void* handle)
{
    glLayout* layout = (glLayout*)handle;
    layout->stride = 0;
    static u32 index = 0;
    
    for (Element& element : layout->elements) {
        element.offset = layout->stride;
        layout->stride += element.size;
    }

    for (const Element& element : layout->elements) {
        u32 count = getDataTypeCount(element.type);
        u32 type = typeToGLType(element.type);
        u32 stride = layout->stride;

        switch (element.type) {
            case PRIME_DATA_TYPE_FLOAT:
            case PRIME_DATA_TYPE_FLOAT2:
            case PRIME_DATA_TYPE_FLOAT3:
            case PRIME_DATA_TYPE_FLOAT4: {
                glVertexAttribPointer(
                    index,
                    count,
                    type,
                    element.normalize,
                    stride,
                    (const void*)element.offset);

                glEnableVertexAttribArray(index);
                glVertexAttribDivisor(index, element.divisor);
                break;
            }

            case PRIME_DATA_TYPE_INT:
            case PRIME_DATA_TYPE_INT2:
            case PRIME_DATA_TYPE_INT3:
            case PRIME_DATA_TYPE_INT4:
            case PRIME_DATA_TYPE_BOOL: {
                glVertexAttribIPointer(
                    index,
                    count,
                    type,
                    stride,
                    (const void*)element.offset);

                glEnableVertexAttribArray(index);
                glVertexAttribDivisor(index, element.divisor);
                break;
            }

        } // switch
        index++;
    }
}

void _glUnbindLayout(void* handle)
{
    glLayout* layout = (glLayout*)handle;
    static u32 index = 0;
    for (const Element& element : layout->elements) {
        switch (element.type) {
            case PRIME_DATA_TYPE_FLOAT:
            case PRIME_DATA_TYPE_FLOAT2:
            case PRIME_DATA_TYPE_FLOAT3:
            case PRIME_DATA_TYPE_FLOAT4: {
                glDisableVertexAttribArray(index);
                break;
            }

            case PRIME_DATA_TYPE_INT:
            case PRIME_DATA_TYPE_INT2:
            case PRIME_DATA_TYPE_INT3:
            case PRIME_DATA_TYPE_INT4:
            case PRIME_DATA_TYPE_BOOL: {
                glDisableVertexAttribArray(index);
                break;
            }

        } // switch
        index++;
    }
}