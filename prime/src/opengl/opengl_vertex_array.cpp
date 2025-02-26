
#include "opengl_vertex_array.h"
#include "prime/logger.h"
#include "opengl_API.h"

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

    GLVertexArray::GLVertexArray()
    {
        m_Index = 0;
        m_Handle = new VertexArrayHandle;
        glGenVertexArrays(1, &m_Handle->id);
        glBindVertexArray(m_Handle->id);
    }
    
    GLVertexArray::~GLVertexArray()
    {
        glDeleteVertexArrays(1, &m_Handle->id);
        m_Handle->id = 0;
        delete m_Handle;
        m_Handle = nullptr;
    }
    
    void
    GLVertexArray::submit(const Ref<VertexBuffer>& vertex_buffer)
    {
        PASSERT_MSG(vertex_buffer.get(), "vertex_buffer is null");

        if (vertex_buffer->getLayout().getElements().size()) {
            const auto& layout = vertex_buffer->getLayout();
            for (const auto& element : layout) {
                u32 count = getTypeCount(element.type);
                u32 type = typeToGLType(element.type);
                u32 stride = layout.getStride();

                switch (element.type) {
                    case Type::Float:
                    case Type::Float2:
                    case Type::Float3:
                    case Type::Float4: {
                        glVertexAttribPointer(
                            m_Index,
                            count,
                            type,
                            element.normalize,
                            stride,
                            (const void*)element.offset);

                        glEnableVertexAttribArray(m_Index);
                        glVertexAttribDivisor(m_Index, element.divisor);
                        break;
                    }

                    case Type::Int:
                    case Type::Int2:
                    case Type::Int3:
                    case Type::Int4:
                    case Type::Bool: {
                        glVertexAttribIPointer(
                            m_Index,
                            count,
                            type,
                            stride,
                            (const void*)element.offset);

                        glEnableVertexAttribArray(m_Index);
                        glVertexAttribDivisor(m_Index, element.divisor);
                        break;
                    }

                    case Type::Mat3:
                    case Type::Mat4: {
                        for (u8 i = 0; i < count; i++) {
                            glVertexAttribPointer(
                                m_Index,
                                count,
                                type,
                                element.normalize,
                                stride,
                                (const void*)(element.offset + sizeof(f32) * count * i));

                            glEnableVertexAttribArray(m_Index);
                            glVertexAttribDivisor(m_Index, element.divisor);
                        }
                        break;
                    }

                } // switch
                m_Index++;
            }
        }
        else {
            PWARN("vertex buffer has no layout");
        }
    }
    
} // namespace prime
