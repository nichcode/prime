
#pragma once

#include "prime/renderer/renderer_API.h"
#include "context_API.h"

namespace prime::renderer {

    class GLRendererAPI : public RendererAPI
    {
    private:
        GraphicsAPI m_API;
        core::Scope<ContextAPI> m_Context;

    public:
        GLRendererAPI(const core::Scope<core::Window>& window);

        virtual void makeActive() override;
        virtual void clear() override;
        virtual void present() override;

        virtual void setClearColor(const Color& color) override;

        virtual GraphicsAPI getAPI() const override { return m_API; }
    };
    
} // namespace prime::renderer