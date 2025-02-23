
#pragma once

#include "prime/context.h"

#ifdef PPLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // PPLATFORM_WINDOWS

namespace prime {

    class GLContext : public Context
    {
    private:
#ifdef PPLATFORM_WINDOWS
        HWND m_Window;
        HGLRC m_Context;
        HDC m_Hdc;
#endif // PPLATFORM_WINDOWS

    public:
        GLContext(const Window& window);
        ~GLContext();

        virtual void
        swapbuffers() override;    
        
        virtual void
        makeActive() override;

        virtual void
        setClearColor(const Color& color) override;

        virtual void
        clear() override;
    };
    
} // namespace prime