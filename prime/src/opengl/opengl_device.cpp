
#include "opengl_device.h"
#include "prime/native.h"
#include "prime/logger.h"
#include "opengl_API.h"
#include "api.h"

#ifdef PPLATFORM_WINDOWS
#include "windows/wgl_context.h"
#endif // PPLATFORM_WINDOWS

#include "opengl/opengl_buffers.h"
#include "opengl/opengl_vertex_array.h"
#include "opengl/opengl_shader.h"
#include "opengl/opengl_textures.h"

namespace prime {

#ifdef PPLATFORM_WINDOWS

struct GLDeviceHandle
{
    HWND window;
    HGLRC context;
    HDC hdc;
};

#endif // PPLATFORM_WINDOWS

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

    GLDevice::GLDevice(const Window& window)
    {
        m_Handle = new GLDeviceHandle();

#ifdef PPLATFORM_WINDOWS
        m_Handle->window = getWin32WindowHandle(window);
        m_Handle->context = wglContextCreate(m_Handle->window);
        m_Handle->hdc = GetDC(m_Handle->window);
#endif // PPLATFORM_WINDOWS

        m_Viewport.x = 0;
        m_Viewport.y = 0;
        m_Viewport.width = window.getWidth();
        m_Viewport.height= window.getHeight();

        glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
    }

    GLDevice::~GLDevice()
    {
#ifdef PPLATFORM_WINDOWS
        wglContextDestroy(m_Handle->context);
#endif // PPLATFORM_WINDOWS

        delete m_Handle;
        m_Handle = nullptr;
    }

    Ref<VertexArray> 
    GLDevice::createVertexArray()
    {
        return createRef<GLVertexArray>();
    }

    Ref<VertexBuffer> 
    GLDevice::createDynamicVertexBuffer(u32 size)
    {
        return createRef<GLVertexBuffer>(size); 
    }

    Ref<VertexBuffer> 
    GLDevice::createStaticVertexBuffer(f32* vertices, u32 size)
    {
        return createRef<GLVertexBuffer>(vertices, size);
    }

    Ref<IndexBuffer> 
    GLDevice::createIndexBuffer(u32* indices, u32 count)
    {
        return createRef<GLIndexBuffer>(indices, count); 
    }

    Ref<Shader> 
    GLDevice::createShader(const ShaderDesc& desc)
    {
        return createRef<GLShader>(desc);
    }
    
    Ref<Texture> 
    GLDevice::createTexture(u32 width, u32 height, TextureUsage usage)
    {
        return createRef<GLTexture>(width, height, usage);
    }
    
    Ref<Texture> 
    GLDevice::createTexture(const str& filepath)
    {
        return createRef<GLTexture>(filepath);
    }  

    void 
    GLDevice::present()
    {
#ifdef PPLATFORM_WINDOWS
        SwapBuffers(m_Handle->hdc);
#endif // PPLATFORM_WINDOWS
    }

    void 
    GLDevice::makeActive()
    {
#ifdef PPLATFORM_WINDOWS
        wglContextMakeCurrent(m_Handle->window, m_Handle->context);
#endif // PPLATFORM_WINDOWS
    }

    void 
    GLDevice::setClearColor(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void 
    GLDevice::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void 
    GLDevice::setViewport(const Rect& viewport)
    {
        glViewport(
            viewport.x,
            viewport.y,
            viewport.width,
            viewport.height);
        
        m_Viewport = viewport;
    }
    
    void 
    GLDevice::setVertexArray(const Ref<VertexArray>& vertex_array)
    {
        if (vertex_array.get()) {
            glBindVertexArray(vertex_array->getHandle()->id);
        }
        else {
            glBindVertexArray(0);
        }
    }
    
    void 
    GLDevice::setVertexBuffer(const Ref<VertexBuffer>& vertex_buffer)
    {
        if (vertex_buffer.get()) {
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->getHandle()->id);
        }
        else {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
    
    void 
    GLDevice::setIndexBuffer(const Ref<IndexBuffer>& index_buffer)
    {
        if (index_buffer.get()) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->getHandle()->id);
        }
        else {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
    
    void 
    GLDevice::setShader(const Ref<Shader>& shader)
    {
        if (shader.get()) {
            glUseProgram(shader->getHandle()->id);
        }
        else {
            glUseProgram(0);
        }
    }
    
    void 
    GLDevice::setTexture(const Ref<Texture>& texture, u32 slot)
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
    GLDevice::setRenderTarget(const Ref<Texture>& texture)
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
    GLDevice::drawElements(DrawMode mode, u32 count)
    {
        GLenum type = drawModeToOpenGL(mode);
        glDrawElements(type, count, GL_UNSIGNED_INT, nullptr);
    }
    
    void GLDevice::drawElementsInstanced(DrawMode mode, u32 count, u32 instance_count)
    {
        GLenum type = drawModeToOpenGL(mode);
        glDrawElementsInstanced(type, count, GL_UNSIGNED_INT, nullptr, instance_count);
    }
    
} // namespace prime
