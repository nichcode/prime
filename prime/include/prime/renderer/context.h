
#pragma once

#include "prime/core/scope.h"
#include "prime/core/window.h"
#include "prime/renderer/color.h"

namespace prime::renderer {

    class Context
    {
    public:
        virtual ~Context() = default;

        virtual void setVsync(b8 vsync = true) = 0;
        virtual void setClearColor(const Color& color) = 0;

        virtual GraphicsAPI getAPI() const = 0;

        virtual void clear() = 0;
        virtual void makeActive() = 0;  
        virtual void present() = 0;    
    
        static core::Scope<Context> create(GraphicsAPI API, const core::Window& window);
    };
    
} // namespace prime::renderer
