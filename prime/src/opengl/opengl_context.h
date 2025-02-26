
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
        std::vector<VertexArray*> m_VertexArrays;
        std::vector<VertexBuffer*> m_VertexBuffers;
        std::vector<IndexBuffer*> m_IndexBuffers;
        std::vector<Layout*> m_Layouts;
        std::vector<Shader*> m_Shaders;
        std::vector<Texture2D*> m_Texture2Ds;

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

        virtual VertexArray*
        createVertexArray() override;

        virtual void
        destroyVertexArray(VertexArray* vertex_array) override;

        virtual VertexBuffer*
        createDynamicVertexBuffer(u32 size) override;

        virtual VertexBuffer*
        createStaticVertexBuffer(f32* vertices, u32 size) override;

        virtual IndexBuffer*
        createIndexBuffer(u32* indices, u32 count) override;

        virtual void
        destroyVertexBuffer(VertexBuffer* vertex_buffer) override;

        virtual void
        destroyIndexBuffer(IndexBuffer* index_buffer) override;

        virtual Shader*
        createShader(const ShaderDesc& desc) override;

        virtual void
        destroyShader(Shader* shader) override;

        virtual Texture2D*
        createTexture2D(u32 width, u32 height) override;

        virtual Texture2D*
        createTexture2D(const str& filepath) override;

        virtual void
        destroyTexture2D(Texture2D* texture) override;

        virtual void
        setVertexArray(const VertexArray* vertex_array) override;

        virtual void
        setVertexBuffer(const VertexBuffer* vertex_buffer) override;

        virtual void
        setIndexBuffer(const IndexBuffer* index_buffer) override;

        virtual void
        setShader(const Shader* shader) override;

        virtual void
        setTexture2D(const Texture2D* texture, u32 slot) override;

        virtual void
        drawElements(DrawMode mode, u32 count) override;
    };
    
} // namespace prime