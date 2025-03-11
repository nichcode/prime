
#pragma once

#include "prime/renderer/renderer_API.h"
#include "context_API.h"

#include <vector>

namespace prime::renderer {

    class GLRendererAPI : public RendererAPI
    {
    private:
        GraphicsAPI m_API;
        core::Scope<ContextAPI> m_Context;

        std::vector<VertexArray*> m_VertexArrays;
        std::vector<VertexBuffer*> m_VertexBuffers;

    public:
        GLRendererAPI(const core::Scope<core::Window>& window);
        virtual ~GLRendererAPI() override;

        virtual VertexArray* createVertexArray() override;
        virtual void deleteVertexArray(VertexArray* vertex_array) override;

        virtual VertexBuffer* createStaticVertexBuffer(f32* vertices, u32 size) override;
        virtual VertexBuffer* createDynamicVertexBuffer(u32 size) override; 
        virtual void deleteVertexBuffer(VertexBuffer* vertex_buffer) override;

        virtual void makeActive() override;
        virtual void clear() override;
        virtual void present() override;

        virtual void setClearColor(const Color& color) override;
        virtual void setVertexBufferData(const VertexBuffer* vertex_buffer, const void* data, u32 size) override;

        virtual void setVertexArray(const VertexArray* vertex_array) override;
         virtual void setVertexBuffer(const VertexBuffer* vertex_buffer) override;

        virtual GraphicsAPI getAPI() const override { return m_API; }
    };
    
} // namespace prime::renderer