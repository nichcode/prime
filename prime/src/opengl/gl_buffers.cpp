
#include "gl_buffers.h"
#include "glad/glad.h"

namespace prime::renderer {

    GLVertexBuffer::GLVertexBuffer(f32* vertices, u32 size)
    {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        m_Dynamic = false;
    }
    
    GLVertexBuffer::GLVertexBuffer(u32 size)
    {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        m_Dynamic = true;
    }
    
    GLVertexBuffer::~GLVertexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
    }
    
    void GLVertexBuffer::setData(const void* data, u32 size)
    {
        if (m_Dynamic) {
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        }
    }
    
    void GLVertexBuffer::bind() const 
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    }
    
    void GLVertexBuffer::unBind() const 
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    
    // indexbuffer
    GLIndexBuffer::GLIndexBuffer(u32* indices, u32 count)
    {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
        m_Count = count;
    }
    
    GLIndexBuffer::~GLIndexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
        m_Count = 0;
    }
    
    void GLIndexBuffer::bind() const 
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    }
    
    void GLIndexBuffer::unBind() const 
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


    // uniformbuffer
    GLUniformBuffer::GLUniformBuffer(u32 size, u32 binding)
    {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_ID);
    }
    
    GLUniformBuffer::~GLUniformBuffer()
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
    }
    
    void GLUniformBuffer::setData(const void* data, u32 size)
    {
        glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
    }
    
    void GLUniformBuffer::bind() const 
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
    }
    
    void GLUniformBuffer::unBind() const 
    {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    
} // namespace prime::renderer
