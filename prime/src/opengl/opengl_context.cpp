
#include "opengl_context.h"
#include "prime/native.h"
#include "prime/logger.h"
#include "glad/glad.h"

#include <algorithm>

#include "opengl_buffers.h"
#include "opengl_vertex_array.h"
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
        m_VertexArrays.clear();
        m_VertexBuffers.clear();
        m_IndexBuffers.clear();
        m_Shaders.clear();
    }

    GLContext::~GLContext()
    {
#ifdef PPLATFORM_WINDOWS
        wglContextDestroy(m_Context);
#endif // PPLATFORM_WINDOWS

        // vertex array
        for (VertexArray* vertex_array : m_VertexArrays) {
            destroyVertexArray(vertex_array);
        }

        // vertex buffer
        for (VertexBuffer* vertex_buffer : m_VertexBuffers) {
            destroyVertexBuffer(vertex_buffer);
        }

        // index buffer
        for (IndexBuffer* vertex_buffer : m_IndexBuffers) {
            destroyIndexBuffer(vertex_buffer);
        }

        // shader
        for (Shader* shader : m_Shaders) {
            destroyShader(shader);
        }

        m_VertexArrays.clear();
        m_VertexBuffers.clear();
        m_IndexBuffers.clear();
        m_Shaders.clear();
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
    
    void 
    GLContext::setViewport(const Rect& viewport)
    {
        glViewport(
            viewport.x,
            viewport.y,
            viewport.width,
            viewport.height);
        
        m_Viewport = viewport;
    }
    
    VertexArray* 
    GLContext::createVertexArray()
    {
        VertexArray* vertex_array = new GLVertexArray();
        m_VertexArrays.push_back(vertex_array);
        return vertex_array;
    }
    
    void 
    GLContext::destroyVertexArray(VertexArray* vertex_array)
    {
        PASSERT_MSG(vertex_array, "vertex_array is null");
        auto it = std::find(m_VertexArrays.begin(), m_VertexArrays.end(), vertex_array);
        if (it != m_VertexArrays.end())
        {
            m_VertexArrays.erase(it);
        }

        delete vertex_array;
    }
    
    VertexBuffer* 
    GLContext::createDynamicVertexBuffer(u32 size)
    {
        VertexBuffer* vertex_buffer = new GLVertexBuffer(size);
        m_VertexBuffers.push_back(vertex_buffer);
        return vertex_buffer;
    }
    
    VertexBuffer* 
    GLContext::createStaticVertexBuffer(f32* vertices, u32 size)
    {
        VertexBuffer* vertex_buffer = new GLVertexBuffer(vertices, size);
        m_VertexBuffers.push_back(vertex_buffer);
        return vertex_buffer;
    }
    
    void 
    GLContext::destroyVertexBuffer(VertexBuffer* vertex_buffer)
    {
        PASSERT_MSG(vertex_buffer, "vertex_buffer is null");
        auto it = std::find(m_VertexBuffers.begin(), m_VertexBuffers.end(), vertex_buffer);
        if (it != m_VertexBuffers.end())
        {
            m_VertexBuffers.erase(it);
        }

        delete vertex_buffer;
    }

    IndexBuffer* 
    GLContext::createIndexBuffer(u32* indices, u32 count)
    {
        IndexBuffer* index_buffer = new GLIndexBuffer(indices, count);
        m_IndexBuffers.push_back(index_buffer);
        return index_buffer;
    }
    
    void 
    GLContext::destroyIndexBuffer(IndexBuffer* index_buffer)
    {
        PASSERT_MSG(index_buffer, "index_buffer is null");
        auto it = std::find(m_IndexBuffers.begin(), m_IndexBuffers.end(), index_buffer);
        if (it != m_IndexBuffers.end())
        {
            m_IndexBuffers.erase(it);
        }

        delete index_buffer;
        
    }

    Shader* 
    GLContext::createShader(const ShaderDesc& desc)
    {
        Shader* shader = new GLShader(desc);
        m_Shaders.push_back(shader);
        return shader;
    }
    
    void 
    GLContext::destroyShader(Shader* shader)
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
    GLContext::setVertexArray(VertexArray* vertex_array)
    {
        glBindVertexArray(vertex_array->getID());
    }
    
    void 
    GLContext::setVertexBuffer(VertexBuffer* vertex_buffer)
    {
        PASSERT_MSG(vertex_buffer, "vertex_buffer is null");
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->getID());
    }
    
    void 
    GLContext::setIndexBuffer(IndexBuffer* index_buffer)
    {
        PASSERT_MSG(index_buffer, "index_buffer is null");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->getID());
    }
    
    void 
    GLContext::setShader(Shader* shader)
    {
        PASSERT_MSG(shader, "shader is null");
        glUseProgram(shader->getID());
    }

    void
    GLContext::drawElements(DrawMode mode, u32 count)
    {
        GLenum type = drawModeToOpenGL(mode);
        glDrawElements(type, count, GL_UNSIGNED_INT, nullptr);
    }
    
} // namespace prime
