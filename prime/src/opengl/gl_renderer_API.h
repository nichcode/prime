
#pragma once

#include "prime/renderer/renderer_API.h"
#include "context_API.h"

namespace prime::renderer {

    class GLRendererAPI : public RendererAPI
    {
    private:
        core::Scope<ContextAPI> m_Context;
        u32 m_Index;
        Viewport m_Viewport;

    public:
        GLRendererAPI(const core::Scope<core::Window>& window);

        virtual core::Ref<VertexArray> createVertexArray() override;

        virtual core::Ref<VertexBuffer> createStaticVertexBuffer(f32* vertices, u32 size) override;
        virtual core::Ref<VertexBuffer> createDynamicVertexBuffer(u32 size) override;
        virtual core::Ref<IndexBuffer> createIndexBuffer(u32* indices, u32 count) override;
        virtual core::Ref<UniformBuffer> createUniformBuffer(u32 size, u32 binding) override;

        virtual core::Ref<Shader> createShader(const str& vertex, const str& pixel, b8 load, SourceType type) override;
        virtual core::Ref<Texture> createTexture(u32 width, u32 height, b8 target, TextureFormat format) override;
        virtual core::Ref<Texture> loadTexture(const str& filepath) override;

        virtual void makeActive() override;
        virtual void clear() override;
        virtual void present() override;

        virtual void submit(DrawType type, DrawMode mode, u32 count) override;

        virtual void setClearColor(const Color& color) override;
        virtual void setVsync(b8 vsync = true) override;
        virtual void setViewport(const Viewport& viewport) override;

        virtual GraphicsAPI getAPI() const override { return GraphicsAPIGL; }
        virtual const Viewport& getViewport() const override { return m_Viewport; }
    };
    
} // namespace prime::renderer