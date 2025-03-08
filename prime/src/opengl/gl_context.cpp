
#include "gl_context.h"
#include "prime/core/logger.h"
#include "opengl_API.h"
#include "prime/internal.h"
#include <algorithm>

#ifdef PRIME_PLATFORM_WINDOWS
#include "win32/wgl_context.h"
#endif // PRIME_PLATFORM_WINDOWS

namespace prime::renderer {

#ifdef PRIME_PLATFORM_WINDOWS

    struct GLContextHandle
    {
        HWND window;
        HGLRC context;
        HDC hdc;
    };

#endif // PRIME_PLATFORM_WINDOWS

    struct VertexArrayHandle
    {
        u32 id = 0;
    };

    struct VertexBufferHandle
    {
        u32 id = 0;
        b8 dynamic = false;
    };

    struct IndexBufferHandle
    {
        u32 id = 0;
        u32 count = 0;
    };

    GLContext::GLContext(GraphicsAPI API, const core::Window& window)
    {
        PRIME_ASSERT_MSG(window.getHandle(), "window is null");

        m_Handle = new GLContextHandle();
        m_API = API;
        m_Viewport.width = window.getWidth();
        m_Viewport.height = window.getHeight();
        m_Index = 0;
#ifdef PRIME_PLATFORM_WINDOWS
        m_Handle->window = internal::getWin32WindowHandle(window);
        m_Handle->context = internal::wglContextCreate(m_Handle->window);
        m_Handle->hdc = GetDC(m_Handle->window);
#endif // PRIME_PLATFORM_WINDOWS   
    }
    
    GLContext::~GLContext()
    {
#ifdef PRIME_PLATFORM_WINDOWS
        internal::wglContextDestroy(m_Handle->context);
#endif // PRIME_PLATFORM_WINDOWS

        // vertex buffers
        for (VertexArray array : m_Arrays) {
            glDeleteBuffers(1, &array.handle->id);
            array.handle->id = 0;
            delete array.handle;
            array.handle = nullptr;
        }

        // index buffers
        for (VertexBuffer buffer : m_VBuffers) {
            glDeleteBuffers(1, &buffer.handle->id);
            buffer.handle->id = 0;
            delete buffer.handle;
            buffer.handle = nullptr;
        }

        // index buffers
        for (IndexBuffer buffer : m_IBuffers) {
            glDeleteBuffers(1, &buffer.handle->id);
            buffer.handle->id = 0;
            buffer.handle->count = 0;
            delete buffer.handle;
            buffer.handle = nullptr;
        }

        m_Arrays.clear();
        m_VBuffers.clear();
        m_IBuffers.clear();

        delete m_Handle;
        m_Handle = nullptr;
    }
    
    VertexArray GLContext::createVertexArray()
    {
        VertexArray array;
        array.handle = new VertexArrayHandle();
        glGenVertexArrays(1, &array.handle->id);
        glBindVertexArray(array.handle->id);

        m_Arrays.push_back(array);
        return array;
    }
    
    void GLContext::deleteVertexArray(VertexArray& array)
    {
        auto it = std::find(m_Arrays.begin(), m_Arrays.end(), array);
        if (it != m_Arrays.end())
        {
            m_Arrays.erase(it);
        }

        glDeleteVertexArrays(1, &array.handle->id);
        array.handle->id = 0;
        delete array.handle;
        array.handle = nullptr;
    }
    
    VertexBuffer GLContext::createVertexBuffer(f32* vertices, u32 size)
    {
        VertexBuffer buffer;
        buffer.handle = new VertexBufferHandle();
        glGenBuffers(1, &buffer.handle->id);
        glBindBuffer(GL_ARRAY_BUFFER, buffer.handle->id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        buffer.handle->dynamic = false;
        m_VBuffers.push_back(buffer);
        return buffer;
    }
    
    VertexBuffer GLContext::createDynamicVertexBuffer(u32 size)
    {
        VertexBuffer buffer;
        buffer.handle = new VertexBufferHandle();
        glGenBuffers(1, &buffer.handle->id);
        glBindBuffer(GL_ARRAY_BUFFER, buffer.handle->id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

        buffer.handle->dynamic = true;
        m_VBuffers.push_back(buffer);
        return buffer;
    }
    
    void GLContext::deleteVertexBuffer(VertexBuffer& buffer)
    {
        auto it = std::find(m_VBuffers.begin(), m_VBuffers.end(), buffer);
        if (it != m_VBuffers.end())
        {
            m_VBuffers.erase(it);
        }

        glDeleteBuffers(1, &buffer.handle->id);
        buffer.handle->id = 0;
        delete buffer.handle;
        buffer.handle = nullptr;
    }
    
    IndexBuffer GLContext::createIndexBuffer(u32* indices, u32 count)
    {
        IndexBuffer buffer;
        buffer.handle = new IndexBufferHandle();
        buffer.handle->count = count;

        glGenBuffers(1, &buffer.handle->id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.handle->id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);

        m_IBuffers.push_back(buffer);
        return buffer;
    }
    
    void GLContext::deleteIndexBuffer(IndexBuffer& buffer)
    {
        auto it = std::find(m_IBuffers.begin(), m_IBuffers.end(), buffer);
        if (it != m_IBuffers.end())
        {
            m_IBuffers.erase(it);
        }
        glDeleteBuffers(1, &buffer.handle->id);
        buffer.handle->id = 0;
        buffer.handle->count = 0;
        delete buffer.handle;
        buffer.handle = nullptr;
    }
    
    void GLContext::setVsync(b8 vsync)
    {
#ifdef PRIME_PLATFORM_WINDOWS
        internal::wglContextSetVsync(vsync);
#endif // PRIME_PLATFORM_WINDOWS     
    }
    
    void GLContext::setClearColor(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    
    void GLContext::setViewport(const Viewport& viewport)
    {
        m_Viewport = viewport;
        glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
    }
    
    void GLContext::setVertexBufferData(const VertexBuffer& buffer, const void* data, u32 size)
    {
        if (buffer.handle->dynamic) {
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        }
        else {
            PRIME_WARN("buffer is static");
        }
    }
    
    void GLContext::setVertexArray(const VertexArray& array)
    {
        glBindVertexArray(array.handle->id);
    }
    
    void GLContext::setVertexBuffer(const VertexBuffer& buffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer.handle->id);
    }
    
    void GLContext::setIndexBuffer(const IndexBuffer& buffer)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.handle->id);
    }

    void GLContext::setLayout(const Layout& layout)
    {
        for (const auto& element : layout) {
            u32 count = getDataTypeCount(element.type);
            u32 type = typeToGLType(element.type);
            u32 stride = layout.getStride();

            switch (element.type) {
                case DataTypeFloat:
                case DataTypeFloat2:
                case DataTypeFloat3:
                case DataTypeFloat4: {
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

                case DataTypeInt:
                case DataTypeInt2:
                case DataTypeInt3:
                case DataTypeInt4:
                case DataTypeBool: {
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

            } // switch

            m_Index++;
        }
    }
    
    u32 GLContext::getIndexBufferCount(const IndexBuffer& buffer) const 
    {
        return buffer.handle->count;
    }
    
    void GLContext::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void GLContext::makeActive()
    {
#ifdef PRIME_PLATFORM_WINDOWS
        internal::wglContextMakeCurrent(m_Handle->window, m_Handle->context);
#endif // PRIME_PLATFORM_WINDOWS 
    }
    
    void GLContext::present()
    {
#ifdef PRIME_PLATFORM_WINDOWS
        SwapBuffers(m_Handle->hdc);
#endif // PRIME_PLATFORM_WINDOWS
    }
    
    void GLContext::submit(DrawType type, DrawMode mode, u32 count)
    {
        GLenum gl_type = drawModeToGL(mode);
        if (type == DrawTypeArrays) {
            glDrawArrays(gl_type, 0, count);
        }
        else if (type == DrawTypeElements) {
            glDrawElements(gl_type, count, GL_UNSIGNED_INT, nullptr);
        }      
    }
    
} // namespace prime::renderer
