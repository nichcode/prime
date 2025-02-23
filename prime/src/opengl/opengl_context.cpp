
#include "opengl_context.h"
#include "prime/native.h"
#include "prime/logger.h"
#include "glad/glad.h"

#include <algorithm>

#ifdef PPLATFORM_WINDOWS
#include "windows/wgl_context.h"
#endif // PPLATFORM_WINDOWS

namespace prime {

    static i32 
    getBufferType(BufferType type)
    {
        switch (type)
        {
            case BufferType::Vertex: {
                return GL_ARRAY_BUFFER;
            }
            break;

            case BufferType::Index: {
                return GL_ELEMENT_ARRAY_BUFFER;
            }
            break;
        }
        return 0;
    }

    static i32 
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
        glBindBuffer(type, 0);
    }

    GLBuffer::~GLBuffer()
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
    }

    void
    GLBuffer::setData(const void* data, u32 size)
    {
        i32 type = getBufferType(m_Type);
        glBufferSubData(type, 0, size, data);
    }


    GLContext::GLContext(const Window& window)
    {
#ifdef PPLATFORM_WINDOWS
        m_Window = getWin32WindowHandle(window);
        m_Context = wglContextCreate(m_Window);
        m_Hdc = GetDC(m_Window);
#endif // PPLATFORM_WINDOWS
        m_Buffers.clear();
    }

    GLContext::~GLContext()
    {
#ifdef PPLATFORM_WINDOWS
        wglContextDestroy(m_Context);
#endif // PPLATFORM_WINDOWS
    }

    void 
    GLContext::swapbuffers()
    {
#ifdef PPLATFORM_WINDOWS
        SwapBuffers(m_Hdc);
#endif // PPLATFORM_WINDOWS
    }

    void 
    GLContext::makeActive()
    {
#ifdef PPLATFORM_WINDOWS
        wglContextMakeCurrent(m_Window, m_Context);
#endif // PPLATFORM_WINDOWS
    }

    void 
    GLContext::setClearColor(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void 
    GLContext::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Buffer*
    GLContext::createBuffer(const BufferDesc& desc)
    {
        Buffer* buffer = new GLBuffer(desc);
        m_Buffers.push_back(buffer);
        return buffer;
    }

    void
    GLContext::destroyBuffer(Buffer* buffer)
    {
        PASSERT_MSG(buffer, "buffer is null");
        auto it = std::find(m_Buffers.begin(), m_Buffers.end(), buffer);
        if (it != m_Buffers.end())
        {
            m_Buffers.erase(it);
        }

        delete buffer;
    }
    
} // namespace prime
