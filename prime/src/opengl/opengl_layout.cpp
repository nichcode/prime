
#include "opengl_layout.h"
#include "pch.h"
#include "opengl_funcs.h"

PRIME_INLINE u32 getDataTypeSize(primeDataType type)
{
    switch (type)
    {
        case primeDataTypes_Int:
        case primeDataTypes_Float: {
            return 4;
        }

        case primeDataTypes_Int2:
        case primeDataTypes_Float2: {
            return 8;
        }

        case primeDataTypes_Int3:
        case primeDataTypes_Float3: {
            return 12;
        }

        case primeDataTypes_Int4:
        case primeDataTypes_Float4: {
            return 16;
        }
        case primeDataTypes_Bool:     return 1;
    }
    return 0;
}

PRIME_INLINE u32 getDataTypeCount(primeDataType type)
{
    switch (type)
    {
        case primeDataTypes_Float:
        case primeDataTypes_Int:
        case primeDataTypes_Bool: {
            return 1;
        }

        case primeDataTypes_Float2:
        case primeDataTypes_Int2: {
            return 2;
        }

        case primeDataTypes_Float3:
        case primeDataTypes_Int3: {
            return 3;
        }

        case primeDataTypes_Float4:
        case primeDataTypes_Int4: {
            return 4;
        }
    }
    return 0;
}

PRIME_INLINE GLenum typeToGLType(primeDataType type)
{
    switch (type)
    {
        case primeDataTypes_Int:
        case primeDataTypes_Int2:
        case primeDataTypes_Int3:
        case primeDataTypes_Int4:
            return GL_INT;

        case primeDataTypes_Float:
        case primeDataTypes_Float2:
        case primeDataTypes_Float3:
        case primeDataTypes_Float4:
            return GL_FLOAT;

        case primeDataTypes_Bool:
            return GL_BOOL;
    }
    return 0;
}

struct Element
{
    primeDataType type = primeDataTypes_Float3;
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
            case primeDataTypes_Float:
            case primeDataTypes_Float2:
            case primeDataTypes_Float3:
            case primeDataTypes_Float4: {
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

            case primeDataTypes_Int:
            case primeDataTypes_Int2:
            case primeDataTypes_Int3:
            case primeDataTypes_Int4:
            case primeDataTypes_Bool: {
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
            case primeDataTypes_Float:
            case primeDataTypes_Float2:
            case primeDataTypes_Float3:
            case primeDataTypes_Float4: {
                glDisableVertexAttribArray(index);
                break;
            }

            case primeDataTypes_Int:
            case primeDataTypes_Int2:
            case primeDataTypes_Int3:
            case primeDataTypes_Int4:
            case primeDataTypes_Bool: {
                glDisableVertexAttribArray(index);
                break;
            }

        } // switch
        index++;
    }
}