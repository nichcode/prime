
#include "gl_context.h"
#include "prime/core/logger.h"
#include "glad/glad.h"
#include "prime/internal.h"

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

    GLContext::GLContext(GraphicsAPI API, const core::Window& window)
    {
        PRIME_ASSERT_MSG(window.getHandle(), "window is null");

        m_Handle = new GLContextHandle();
        m_API = API;
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
        delete m_Handle;
        m_Handle = nullptr;
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
    
} // namespace prime::renderer
