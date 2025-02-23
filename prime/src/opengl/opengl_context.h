
#pragma once

#include "prime/context.h"

#ifdef PPLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // PPLATFORM_WINDOWS

#include <vector>

namespace prime {

    class GLBuffer : public Buffer
    {
    private:
        u32 m_ID;
        BufferType m_Type;
        BufferUsage m_Usage;

    public:
        GLBuffer(const BufferDesc& desc);
        virtual ~GLBuffer() override;

        virtual void
        setData(const void* data, u32 size) override;
    };

    class GLContext : public Context
    {
    private:
#ifdef PPLATFORM_WINDOWS
        HWND m_Window;
        HGLRC m_Context;
        HDC m_Hdc;
#endif // PPLATFORM_WINDOWS

        std::vector<Buffer*> m_Buffers;

    public:
        GLContext(const Window& window);
        ~GLContext() override;

        virtual void
        swapbuffers() override;    
        
        virtual void
        makeActive() override;

        virtual void
        setClearColor(const Color& color) override;

        virtual void
        clear() override;

        virtual Buffer*
        createBuffer(const BufferDesc& desc) override;

        virtual void
        destroyBuffer(Buffer* buffer) override;
    };
    
} // namespace prime