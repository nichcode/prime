
#include "opengl_context.h"
#include "prime/native.h"
#include "prime/logger.h"
#include "glad/glad.h"

#include <algorithm>

#include "opengl_API.h"
#include "opengl_buffer.h"
#include "opengl_layout.h"
#include "opengl_shader.h"

#ifdef PPLATFORM_WINDOWS
#include "windows/wgl_context.h"
#endif // PPLATFORM_WINDOWS

namespace prime {

    PINLINE static 
    GLenum drawModeToOpenGL(DrawMode mode)
    {
        switch (mode)
        {
        case DrawMode::Triangles:
            return GL_TRIANGLES;
            break;

        case DrawMode::Lines:
            return GL_LINES;
            break;
        }
        return 0;
    }

    GLContext::GLContext(const Window& window)
    {
#ifdef PPLATFORM_WINDOWS
        m_Window = getWin32WindowHandle(window);
        m_Context = wglContextCreate(m_Window);
        m_Hdc = GetDC(m_Window);
#endif // PPLATFORM_WINDOWS
        m_Buffers.clear();
        m_Layouts.clear();
    }

    GLContext::~GLContext()
    {
#ifdef PPLATFORM_WINDOWS
        wglContextDestroy(m_Context);
#endif // PPLATFORM_WINDOWS

    for (Buffer* buffer : m_Buffers) {
        destroyBuffer(buffer);
    }

    for (Layout* layout : m_Layouts) {
        destroyLayout(layout);
    }

    m_Buffers.clear();
    m_Layouts.clear();
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
    
    void GLContext::setViewport(const Rect& viewport)
    {
        glViewport(
            viewport.x,
            viewport.y,
            viewport.width,
            viewport.height);
        
        m_Viewport = viewport;
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

    Layout*
    GLContext::createLayout()
    {
        Layout* layout = new GLLayout();
        m_Layouts.push_back(layout);
        return layout;
    }

    void
    GLContext::destroyLayout(Layout* layout)
    {
        PASSERT_MSG(layout, "layout is null");
        auto it = std::find(m_Layouts.begin(), m_Layouts.end(), layout);
        if (it != m_Layouts.end())
        {
            m_Layouts.erase(it);
        }

        delete layout;
    }
    
    Shader* GLContext::createShader(const ShaderDesc& desc)
    {
        Shader* shader = new GLShader(desc);
        m_Shaders.push_back(shader);
        return shader;
    }
    
    void GLContext::destroyShader(Shader* shader)
    {
        PASSERT_MSG(shader, "shader is null");
        auto it = std::find(m_Shaders.begin(), m_Shaders.end(), shader);
        if (it != m_Shaders.end())
        {
            m_Shaders.erase(it);
        }

        delete shader;
    }

    void
    GLContext::setLayout(Layout* layout, b8 submit)
    {
        glBindVertexArray(layout->getID());
    }

    void
    GLContext::setBuffer(Buffer* buffer)
    {
        i32 type = getBufferType(buffer->getType());
        glBindBuffer(type, buffer->getID());
    }
    
    void GLContext::setShader(Shader* shader)
    {
        glUseProgram(shader->getID());
    }

    void
    GLContext::drawElements(DrawMode mode, u32 count)
    {
        GLenum type = drawModeToOpenGL(mode);
        glDrawElements(type, count, GL_UNSIGNED_INT, nullptr);
    }
    
} // namespace prime
