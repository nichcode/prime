
#include "opengl_buffers.h"
#include "opengl_API.h"

namespace prime {

    GLVertexBuffer::GLVertexBuffer(f32* vertices, u32 size)
    {
        m_Handle = new VertexBufferHandle();
        
        glGenBuffers(1, &m_Handle->id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Handle->id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    
    GLVertexBuffer::GLVertexBuffer(u32 size)
    {
        m_Handle = new VertexBufferHandle();
        glGenBuffers(1, &m_Handle->id);
        glBindBuffer(GL_ARRAY_BUFFER, m_Handle->id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    GLVertexBuffer::~GLVertexBuffer()
    {
        glDeleteBuffers(1, &m_Handle->id);
        m_Handle->id = 0;
        delete m_Handle;
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
        m_Handle = new IndexBufferHandle();
        glGenBuffers(1, &m_Handle->id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle->id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
        m_Count = count;
    }

    GLIndexBuffer::~GLIndexBuffer()
    {
        glDeleteBuffers(1, &m_Handle->id);
        m_Handle->id = 0;
        delete m_Handle;
        m_Handle = nullptr;
        m_Count = 0;
    }
    
    
    GLUniformBuffer::GLUniformBuffer(u32 size, u32 binding)
    {
        m_Handle = new UniformBufferHandle();
        glGenBuffers(1, &m_Handle->id);
        glBindBuffer(GL_UNIFORM_BUFFER, m_Handle->id);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_Handle->id);
    }
    
    GLUniformBuffer::~GLUniformBuffer()
    {
        glDeleteBuffers(1, &m_Handle->id);
        m_Handle->id = 0;
        delete m_Handle;
        m_Handle = nullptr;
    }
    
    void 
    GLUniformBuffer::setData(const void* data, u32 size)
    {
        glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
    }

} // namespace prime
