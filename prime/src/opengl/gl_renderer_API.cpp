
#include "gl_renderer_API.h"
#include "prime/internal.h"
#include "opengl_API.h"

#include "windows/windows_gl_context.h"
#include "gl_buffers.h"
#include "gl_shader.h"
#include "gl_texture.h"
#include "gl_vertex_array.h"

namespace prime::renderer {

    GLRendererAPI::GLRendererAPI(const core::Scope<core::Window>& window)
    {
#ifdef PRIME_PLATFORM_WINDOWS
        HWND handle = internal::getWin32WindowHandle(window);
        m_Context = core::createScope<WindowsGLContext>(handle);
#endif // PRIME_PLATFORM_WINDOWS
        
        m_Index = 0;
        m_Viewport.width = window->getWidth();
        m_Viewport.height = window->getHeight();
    }
    
    core::Ref<VertexArray> GLRendererAPI::createVertexArray()
    {
        return core::createRef<GLVertexArray>();
    }
    
    core::Ref<VertexBuffer> GLRendererAPI::createStaticVertexBuffer(f32* vertices, u32 size)
    {
        return core::createRef<GLVertexBuffer>(vertices, size);
    }
    
    core::Ref<VertexBuffer> GLRendererAPI::createDynamicVertexBuffer(u32 size)
    {
        return core::createRef<GLVertexBuffer>(size);
    }
    
    core::Ref<IndexBuffer> GLRendererAPI::createIndexBuffer(u32* indices, u32 count)
    {
        return core::createRef<GLIndexBuffer>(indices, count);
    }
    
    core::Ref<UniformBuffer> GLRendererAPI::createUniformBuffer(u32 size, u32 binding)
    {
        return core::createRef<GLUniformBuffer>(size, binding);
    }
    
    core::Ref<Shader> GLRendererAPI::createShader(const str& vertex, const str& pixel, b8 load, SourceType type)
    {
        return core::createRef<GLShader>(vertex, pixel, load, type);
    }
    
    core::Ref<Texture> GLRendererAPI::createTexture(u32 width, u32 height, b8 target, TextureFormat format)
    {
        return core::createRef<GLTexture>(width, height, target, format);
    }
    
    core::Ref<Texture> GLRendererAPI::loadTexture(const str& filepath)
    {
        return core::createRef<GLTexture>(filepath);
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
    
    void GLRendererAPI::submit(DrawType type, DrawMode mode, u32 count)
    {
        GLenum gl_type = drawModeToGL(mode);
        if (type == DrawTypeArrays) {
            glDrawArrays(gl_type, 0, count);
        }
        else if (type == DrawTypeElements) {
            glDrawElements(gl_type, count, GL_UNSIGNED_INT, nullptr);
        }      
    }
    
    void GLRendererAPI::setClearColor(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    
    void GLRendererAPI::setVsync(b8 vsync)
    {
        m_Context->setVsync(vsync);
    }
    
    void GLRendererAPI::setViewport(const Viewport& viewport)
    {
        m_Viewport = viewport;
        glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
    }
    
} // namespace prime::renderer
