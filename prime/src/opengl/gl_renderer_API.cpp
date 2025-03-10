
#include "gl_renderer_API.h"
#include "prime/internal.h"
#include "glad/glad.h"

#include "windows/windows_gl_context.h"

namespace prime::renderer {

    GLRendererAPI::GLRendererAPI(const core::Scope<core::Window>& window)
    {
#ifdef PRIME_PLATFORM_WINDOWS
        HWND handle = internal::getWin32WindowHandle(window);
        m_Context = core::createScope<WindowsGLContext>(handle);
#endif // PRIME_PLATFORM_WINDOWS
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
    
} // namespace prime::renderer
