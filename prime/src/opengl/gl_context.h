
#pragma once

#include "prime/renderer/context.h"
#include <vector>

namespace prime::renderer {

    struct GLContextHandle;

    class GLContext : public Context
    {
    private:
        b8 m_Vsync;
        GraphicsAPI m_API;
        GLContextHandle* m_Handle;
        std::vector<VertexArray> m_Arrays;
        std::vector<VertexBuffer> m_VBuffers;
        std::vector<IndexBuffer> m_IBuffers;

    public:
        GLContext(GraphicsAPI API, const core::Window& window);
        virtual ~GLContext() override;

        virtual VertexArray createVertexArray() override;
        virtual void deleteVertexArray(VertexArray& array) override;

        virtual VertexBuffer createVertexBuffer(f32* vertices, u32 size) override;
        virtual VertexBuffer createDynamicVertexBuffer(u32 size) override; 
        virtual void deleteVertexBuffer(VertexBuffer& buffer) override;

        virtual IndexBuffer createIndexBuffer(u32* indices, u32 count) override;
        virtual void deleteIndexBuffer(IndexBuffer& buffer) override;

        virtual void setVsync(b8 vsync = true) override; 
        virtual void setClearColor(const Color& color) override;

        virtual void setVertexArray(const VertexArray& array) override;
        virtual void setVertexBuffer(const VertexBuffer& buffer) override;
        virtual void setIndexBuffer(const IndexBuffer& buffer) override;

        virtual GraphicsAPI getAPI() const override { return m_API; }

        virtual void clear() override;
        virtual void makeActive() override;  
        virtual void present() override;
    };
    
} // namespace prime::renderer
