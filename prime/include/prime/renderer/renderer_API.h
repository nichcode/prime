
#pragma once

#include "prime/core/scope.h"
#include "prime/core/window.h"
#include "color.h"

namespace prime::renderer {

    PRIME_HANDLE(VertexArray);
    PRIME_HANDLE(VertexBuffer);

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;

        virtual VertexArray* createVertexArray() = 0;
        virtual void deleteVertexArray(VertexArray* vertex_array) = 0;

        virtual VertexBuffer* createStaticVertexBuffer(f32* vertices, u32 size) = 0;
        virtual VertexBuffer* createDynamicVertexBuffer(u32 size) = 0; 
        virtual void deleteVertexBuffer(VertexBuffer* vertex_buffer) = 0;

        virtual void makeActive() = 0;
        virtual void clear() = 0;
        virtual void present() = 0;

        virtual void setClearColor(const Color& color) = 0;
        virtual void setVertexBufferData(const VertexBuffer* vertex_buffer, const void* data, u32 size) = 0;

        virtual void setVertexArray(const VertexArray* vertex_array) = 0;
        virtual void setVertexBuffer(const VertexBuffer* vertex_buffer) = 0;

        virtual GraphicsAPI getAPI() const = 0;
    };
    
} // namespace prime::renderer