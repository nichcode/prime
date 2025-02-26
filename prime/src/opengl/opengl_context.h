
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

        Rect m_Viewport;

    public:
        GLContext(const Window& window);
        ~GLContext() override;

        virtual void
        present() override;    
        
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

        virtual void
        setVertexArray(const Ref<VertexArray>& vertex_array) override;

        virtual void
        setVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) override;

        virtual void
        setIndexBuffer(const Ref<IndexBuffer>& index_buffer) override;

        virtual void
        setShader(const Ref<Shader>& shader) override;

        virtual void
        setTexture(const Ref<Texture>& texture, u32 slot) override;

        virtual void
        setRenderTarget(const Ref<Texture>& texture) override;

        virtual void
        drawElements(DrawMode mode, u32 count) override;
    };
    
} // namespace prime