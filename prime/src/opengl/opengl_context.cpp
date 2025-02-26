
#include "opengl_context.h"
#include "prime/native.h"
#include "prime/logger.h"
#include "opengl_API.h"

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

        m_Viewport.x = 0;
        m_Viewport.y = 0;
        m_Viewport.width = window.getWidth();
        m_Viewport.height= window.getHeight();
    }

    GLContext::~GLContext()
    {
#ifdef PPLATFORM_WINDOWS
        wglContextDestroy(m_Context);
#endif // PPLATFORM_WINDOWS
    }

    void 
    GLContext::present()
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
    
    void 
    GLContext::setVertexArray(const Ref<VertexArray>& vertex_array)
    {
        if (vertex_array.get()) {
            glBindVertexArray(vertex_array->getHandle()->id);
        }
        else {
            glBindVertexArray(0);
        }
    }
    
    void 
    GLContext::setVertexBuffer(const Ref<VertexBuffer>& vertex_buffer)
    {
        if (vertex_buffer.get()) {
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->getHandle()->id);
        }
        else {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
    
    void 
    GLContext::setIndexBuffer(const Ref<IndexBuffer>& index_buffer)
    {
        if (index_buffer.get()) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->getHandle()->id);
        }
        else {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
    
    void 
    GLContext::setShader(const Ref<Shader>& shader)
    {
        if (shader.get()) {
            glUseProgram(shader->getHandle()->id);
        }
        else {
            glUseProgram(0);
        }
    }
    
    void 
    GLContext::setTexture(const Ref<Texture>& texture, u32 slot)
    {
        if (texture.get()) {
            if (slot >= PMAX_TEXTURE_SLOTS) {
                glActiveTexture(GL_TEXTURE15);
                PWARN("texture slot out of bounds. Setting texture to first slot");
            }
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, texture->getHandle()->id);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
    
    void 
    GLContext::setRenderTarget(const Ref<Texture>& texture)
    {
        if (texture.get()) {
            if (texture->getUsage() == TextureUsage::RenderTarget) {
                u32 width = texture->getWidth();
                u32 height = texture->getHeight();
                glBindFramebuffer(GL_FRAMEBUFFER, texture->getHandle()->buffer);
                glViewport(0, 0, width, height);
            }
            else {
                PINFO("Texture is not a render target");
            }
        }
        else {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(m_Viewport.x, m_Viewport.y, m_Viewport.width, m_Viewport.height);
        }
    }

    void
    GLContext::drawElements(DrawMode mode, u32 count)
    {
        GLenum type = drawModeToOpenGL(mode);
        glDrawElements(type, count, GL_UNSIGNED_INT, nullptr);
    }
    
} // namespace prime
