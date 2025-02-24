
#include "opengl_layout.h"
#include "glad/glad.h"

namespace prime {

    PINLINE static GLenum
    typeToGLType(Type type)
    {
        switch (type)
        {
        case Type::Int:
        case Type::Int2:
        case Type::Int3:
        case Type::Int4:
            return GL_INT;

        case Type::Float:
        case Type::Float2:
        case Type::Float3:
        case Type::Float4:
        case Type::Mat3:
        case Type::Mat4:
            return GL_FLOAT;

        case Type::Bool:
            return GL_BOOL;
        }
        return 0;
    }
    
    PINLINE static GLenum
    normalizeToGLType(b8 normalize)
    {
        if (normalize) {
            return GL_TRUE;
        }
        else {
            return GL_FALSE;
        }
    }

    GLLayout::GLLayout()
    {
        glGenVertexArrays(1, &m_ID);
        glBindVertexArray(m_ID);
        m_Unused = &m_ID;
    }

    GLLayout::~GLLayout()
    {
        glDeleteVertexArrays(1, &m_ID);
        m_Elements.clear();
    }

    void 
    GLLayout::add(Type type, u32 divisor, b8 normalize)
    {
        Element element;
        element.type = type;
        element.divisor = divisor;
        element.size = typeGetSize(type);
        element.normalized = normalize;
        m_Elements.push_back(element);
    }

    void
    GLLayout::submit()
    {
        u32 m_Stride = 0;
        for (auto& element : m_Elements) {
            element.offset = m_Stride;
            m_Stride += element.size;
        }

        u32 index = 0;
        for (const auto& element : m_Elements) {
            switch (element.type) {
                case Type::Float:
                case Type::Float2:
                case Type::Float3:
                case Type::Float4: {
                    glEnableVertexAttribArray(index);
                    glVertexAttribPointer(index,
                        typeGetCount(element.type),
                        typeToGLType(element.type),
                        normalizeToGLType(element.normalized),
                        m_Stride,
                        (const void*)element.offset);
                    
                    glVertexAttribDivisor(index, element.divisor);
                    break;
                }
                
                case Type::Int:
                case Type::Int2:
                case Type::Int3:
                case Type::Int4:
                case Type::Bool: {
                    glEnableVertexAttribArray(index);
                    glVertexAttribIPointer(index,
                        typeGetCount(element.type),
                        typeToGLType(element.type),
                        m_Stride,
                        (const void*)element.offset);
                    
                    glVertexAttribDivisor(index, element.divisor);
                    break;
                }
                
                case Type::Mat3:
                case Type::Mat4: {
                    u8 count = count;
                    for (u8 i = 0; i < count; i++)
                    {
                        glEnableVertexAttribArray(index);
                        glVertexAttribPointer(index,
                            count,
                            typeToGLType(element.type),
                            normalizeToGLType(element.normalized),
                            m_Stride,
                            (const void*)(element.offset + sizeof(f32) * count * i));
                        glVertexAttribDivisor(index, element.divisor);
                    }
                    break;
                }
            
            }
            index++;
        }
    }
    
} // namespace prime
