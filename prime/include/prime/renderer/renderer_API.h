
#pragma once

#include "prime/core/scope.h"
#include "prime/core/window.h"
#include "color.h"

namespace prime::renderer {

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;

        virtual void makeActive() = 0;
        virtual void clear() = 0;
        virtual void present() = 0;

        virtual void setClearColor(const Color& color) = 0;

        virtual GraphicsAPI getAPI() const = 0;
    };
    
} // namespace prime::renderer