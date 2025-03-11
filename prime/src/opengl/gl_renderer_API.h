
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

    public:
        GLRendererAPI(const core::Scope<core::Window>& window);
        virtual ~GLRendererAPI() override;

        virtual VertexArray* createVertexArray() override;
        virtual void deleteVertexArray(VertexArray* vertex_array) override;

        virtual void makeActive() override;
        virtual void clear() override;
        virtual void present() override;

        virtual void setClearColor(const Color& color) override;

        virtual void setVertexArray(const VertexArray* vertex_array) override;

        virtual GraphicsAPI getAPI() const override { return m_API; }
    };
    
} // namespace prime::renderer