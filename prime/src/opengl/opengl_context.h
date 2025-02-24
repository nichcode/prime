
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

    class GLContext : public Context
    {
    private:
#ifdef PPLATFORM_WINDOWS
        HWND m_Window;
        HGLRC m_Context;
        HDC m_Hdc;
#endif // PPLATFORM_WINDOWS

        Rect m_Viewport;
        std::vector<Buffer*> m_Buffers;
        std::vector<Layout*> m_Layouts;
        std::vector<Shader*> m_Shaders;

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

        virtual void
        setViewport(const Rect& viewport) override;

        virtual const Rect&
        getViewport() const override { return m_Viewport; }

        virtual Buffer*
        createBuffer(const BufferDesc& desc) override;

        virtual void
        destroyBuffer(Buffer* buffer) override;

        virtual Layout*
        createLayout() override;

        virtual void
        destroyLayout(Layout* layout) override;

        virtual Shader*
        createShader(const ShaderDesc& desc) override;

        virtual void
        destroyShader(Shader* shader) override;

        virtual void
        setLayout(Layout* layout, b8 submit) override;

        virtual void
        setBuffer(Buffer* buffer) override;

        virtual void
        setShader(Shader* shader) override;

        virtual void
        drawElements(DrawMode mode, u32 count) override;
    };
    
} // namespace prime