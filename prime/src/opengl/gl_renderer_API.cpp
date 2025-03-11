
#include "gl_renderer_API.h"
#include "prime/internal.h"
#include "prime/core/logger.h"
#include "opengl_API.h"
#include <algorithm>

#include "windows/windows_gl_context.h"

namespace prime::renderer {

    struct VertexArray
    {
        u32 id = 0;
    };

    struct VertexBuffer
    {
        u32 id = 0;
        b8 dynamic = false;
    };

    GLRendererAPI::GLRendererAPI(const core::Scope<core::Window>& window)
    {
#ifdef PRIME_PLATFORM_WINDOWS
        HWND handle = internal::getWin32WindowHandle(window);
        m_Context = core::createScope<WindowsGLContext>(handle);
#endif // PRIME_PLATFORM_WINDOWS
    }
    
    GLRendererAPI::~GLRendererAPI()
    {
        // vertex arrays
        for (VertexArray* vertex_array : m_VertexArrays) {
            glDeleteBuffers(1, &vertex_array->id);
            vertex_array->id = 0;
            delete vertex_array;
            vertex_array = nullptr;
        }

        // vertex buffers
        for (VertexBuffer* vertex_buffer : m_VertexBuffers) {
            glDeleteBuffers(1, &vertex_buffer->id);
            vertex_buffer->id = 0;
            delete vertex_buffer;
            vertex_buffer = nullptr;
        }

        m_VertexArrays.clear();
        m_VertexBuffers.clear();
    }
    
    VertexArray* GLRendererAPI::createVertexArray()
    {
        VertexArray* vertex_array = new VertexArray();
        glGenVertexArrays(1, &vertex_array->id);
        glBindVertexArray(vertex_array->id);

        m_VertexArrays.push_back(vertex_array);
        return vertex_array;
    }
    
    void GLRendererAPI::deleteVertexArray(VertexArray* vertex_array)
    {
        PRIME_ASSERT_MSG(vertex_array, "vertex array is null");

        auto it = std::find(m_VertexArrays.begin(), m_VertexArrays.end(), vertex_array);
        if (it != m_VertexArrays.end())
        {
            m_VertexArrays.erase(it);
        }

        glDeleteVertexArrays(1, &vertex_array->id);
        vertex_array->id = 0;
        delete vertex_array;
        vertex_array = nullptr;
    }
    
    VertexBuffer* GLRendererAPI::createStaticVertexBuffer(f32* vertices, u32 size)
    {
        VertexBuffer* vertex_buffer = new VertexBuffer();
        glGenBuffers(1, &vertex_buffer->id);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        vertex_buffer->dynamic = false;
        m_VertexBuffers.push_back(vertex_buffer);
        return vertex_buffer;
    }
    
    VertexBuffer* GLRendererAPI::createDynamicVertexBuffer(u32 size)
    {
        VertexBuffer* vertex_buffer = new VertexBuffer();
        glGenBuffers(1, &vertex_buffer->id);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

        vertex_buffer->dynamic = true;
        m_VertexBuffers.push_back(vertex_buffer);
        return vertex_buffer;
    }
    
    void GLRendererAPI::deleteVertexBuffer(VertexBuffer* vertex_buffer)
    {
        PRIME_ASSERT_MSG(vertex_buffer, "vertex buffer is null");

        auto it = std::find(m_VertexBuffers.begin(), m_VertexBuffers.end(), vertex_buffer);
        if (it != m_VertexBuffers.end())
        {
            m_VertexBuffers.erase(it);
        }

        glDeleteBuffers(1, &vertex_buffer->id);
        vertex_buffer->id = 0;
        delete vertex_buffer;
        vertex_buffer = nullptr;
    }
    
    void GLRendererAPI::makeActive()
    {
        m_Context->makeActive();
    }
    
    void GLRendererAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void GLRendererAPI::present()
    {
        m_Context->present();
    }
    
    void GLRendererAPI::setClearColor(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    
    void GLRendererAPI::setVertexBufferData(const VertexBuffer* vertex_buffer, const void* data, u32 size)
    {
        PRIME_ASSERT_MSG(vertex_buffer, "vertex buffer is null");

        if (vertex_buffer->dynamic) {
            glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
        }
        else {
            PRIME_WARN("vertex_buffer is static");
        }
    }
    
    void GLRendererAPI::setVertexArray(const VertexArray* vertex_array)
    {
        PRIME_ASSERT_MSG(vertex_array, "vertex array is null");
        glBindVertexArray(vertex_array->id);
    }
    
    void GLRendererAPI::setVertexBuffer(const VertexBuffer* vertex_buffer)
    {
        PRIME_ASSERT_MSG(vertex_buffer, "vertex buffer is null");
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->id);
    }
    
} // namespace prime::renderer
