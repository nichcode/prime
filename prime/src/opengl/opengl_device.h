
#pragma once

#include "prime/device.h"

namespace prime {

    struct GLDeviceHandle;

    class GLDevice : public Device
    {
    private:
        GLDeviceHandle* m_Handle;
        Rect m_Viewport;

    public:
        GLDevice(const Window& window);
        virtual ~GLDevice() override;

        virtual Ref<VertexArray>
        createVertexArray() override;

        virtual Ref<VertexBuffer>
        createDynamicVertexBuffer(u32 size) override;

        virtual Ref<VertexBuffer>
        createStaticVertexBuffer(f32* vertices, u32 size) override;

        virtual Ref<IndexBuffer>
        createIndexBuffer(u32* indices, u32 count) override;

        virtual Ref<UniformBuffer> 
        createUniformBuffer(u32 size, u32 binding) override;

        virtual Ref<Shader>
        createShader(const ShaderDesc& desc) override;

        virtual Ref<Texture>
        createTexture(u32 width, u32 height, TextureUsage usage) override;

        virtual Ref<Texture>
        createTexture(const str& filepath) override;

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
        setUniformBuffer(const Ref<UniformBuffer>& uniform_buffer) override;

        virtual void
        setShader(const Ref<Shader>& shader) override;

        virtual void
        setTexture(const Ref<Texture>& texture, u32 slot  = 0) override;

        virtual void
        setRenderTarget(const Ref<Texture>& texture) override;

        virtual void
        drawElements(DrawMode mode, u32 count) override;

        virtual void
        drawElementsInstanced(DrawMode mode, u32 count, u32 instance_count) override;
    };
    
} // namespace prime
