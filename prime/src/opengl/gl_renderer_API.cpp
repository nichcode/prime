
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

        m_VertexArrays.clear();
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
    
    void GLRendererAPI::setVertexArray(const VertexArray* vertex_array)
    {
        PRIME_ASSERT_MSG(vertex_array, "vertex array is null");
        glBindVertexArray(vertex_array->id);
    }
    
} // namespace prime::renderer
