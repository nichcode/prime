
#pragma once

#include "prime/renderer/context.h"

namespace prime::renderer {

    struct GLContextHandle;

    class GLContext : public Context
    {
    private:
        b8 m_Vsync;
        GraphicsAPI m_API;
        GLContextHandle* m_Handle;

    public:
        GLContext(GraphicsAPI API, const core::Window& window);
        virtual ~GLContext() override;

        virtual void setVsync(b8 vsync = true) override; 
        virtual void setClearColor(const Color& color) override;

        virtual GraphicsAPI getAPI() const override { return m_API; }

        virtual void clear() override;
        virtual void makeActive() override;  
        virtual void present() override;
    };
    
} // namespace prime::renderer
