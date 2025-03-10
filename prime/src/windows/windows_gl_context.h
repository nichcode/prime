
#pragma once

#include "context_API.h"
#include "windows_API.h"

namespace prime::renderer {

    class WindowsGLContext : public ContextAPI
    {
    private:
        HWND m_Window;
        HGLRC m_Handle;
        HDC m_Device;

    public:
        WindowsGLContext(HWND window);
        virtual ~WindowsGLContext() override;

        virtual void present() override;
        virtual void makeActive() override;
        virtual void setVsync(b8 vsync) override;
    };
    
} // namespace prime::renderer
