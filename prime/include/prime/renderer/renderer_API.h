
#pragma once

#include "prime/core/scope.h"
#include "prime/core/window.h"
#include "color.h"

namespace prime::renderer {

    PRIME_HANDLE(VertexArray);

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;

        virtual VertexArray* createVertexArray() = 0;
        virtual void deleteVertexArray(VertexArray* vertex_array) = 0;

        virtual void makeActive() = 0;
        virtual void clear() = 0;
        virtual void present() = 0;

        virtual void setClearColor(const Color& color) = 0;

        virtual void setVertexArray(const VertexArray* vertex_array) = 0;

        virtual GraphicsAPI getAPI() const = 0;
    };
    
} // namespace prime::renderer