
#include "opengl_buffer.h"
#include "opengl_API.h"
#include "glad/glad.h"

namespace prime {

    PINLINE static i32 
    getBufferUsage(BufferUsage usage)
    {
        switch (usage)
        {
            case BufferUsage::DynamicDraw: {
                return GL_DYNAMIC_DRAW;
            }
            break;

            case BufferUsage::StaticDraw: {
                return GL_STATIC_DRAW;
            }
            break;
        }
        return 0;
    }

    GLBuffer::GLBuffer(const BufferDesc& desc)
    {
        i32 type = getBufferType(desc.type);
        i32 usage = getBufferUsage(desc.usage);
        m_Usage = desc.usage;
        m_Type = desc.type;
        glGenBuffers(1, &m_ID);
        glBindBuffer(type, m_ID);
        glBufferData(type, desc.size, desc.data, usage);
        m_Unused = &m_ID;
    }

    GLBuffer::~GLBuffer()
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
        m_Unused = nullptr;
    }

    void
    GLBuffer::setData(const void* data, u32 size)
    {
        if (m_Usage == BufferUsage::DynamicDraw) {
            i32 type = getBufferType(m_Type);
            glBufferSubData(type, 0, size, data);
        }
    }
    
} // namespace prime
