
#include "windows/windows_gl_context.h"
#include "wgl_context.h"

namespace prime::renderer {

    WindowsGLContext::WindowsGLContext(HWND window)
    {
        m_Window = window;
        m_Handle = internal::wglContextCreate(m_Window);
        m_Device = GetDC(m_Window);
    }
    
    WindowsGLContext::~WindowsGLContext()
    {
        internal::wglContextDestroy(m_Handle);
        ReleaseDC(m_Window, m_Device);
        m_Window = 0;
        m_Handle = 0;
        m_Device = 0;
    }
    
    void WindowsGLContext::present()
    {
        SwapBuffers(m_Device);
    }
    
    void WindowsGLContext::makeActive()
    {
        internal::wglContextMakeCurrent(m_Window, m_Handle);
    }
    
    void WindowsGLContext::setVsync(b8 vsync)
    {
        internal::wglContextSetVsync(vsync);
    }
   
} // namespace prime::renderer
