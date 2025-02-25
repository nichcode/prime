
#include "opengl_buffers.h"
#include "glad/glad.h"

namespace prime {

    GLVertexBuffer::GLVertexBuffer(f32* vertices, u32 size)
    {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        m_Handle = &m_ID;
    }
    
    GLVertexBuffer::GLVertexBuffer(u32 size)
    {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        m_Handle = &m_ID;
    }

    GLVertexBuffer::~GLVertexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
        m_Handle = nullptr;
    }

    void
    GLVertexBuffer::setData(const void* data, u32 size)
    {
        if (m_Dynamic) {
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        }
    }
    
    
    GLIndexBuffer::GLIndexBuffer(u32* indices, u32 count)
    {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
        m_Handle = &m_ID;
        m_Count = count;
    }

    GLIndexBuffer::~GLIndexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
        m_Handle = nullptr;
        m_Count = 0;
    }

} // namespace prime
