
#pragma once

#include "prime/core/scope.h"
#include "prime/core/window.h"
#include "prime/renderer/color.h"

namespace prime::renderer {

    PRIME_HANDLE(VertexArrayHandle);
    PRIME_HANDLE(VertexBufferHandle);
    PRIME_HANDLE(IndexBufferHandle);

    PRIME_HANDLE_DEF(VertexArray, VertexArrayHandle);
    PRIME_HANDLE_DEF(VertexBuffer, VertexBufferHandle);
    PRIME_HANDLE_DEF(IndexBuffer, IndexBufferHandle);

    class Context
    {
    public:
        virtual ~Context() = default;

        virtual VertexArray createVertexArray() = 0;
        virtual void deleteVertexArray(VertexArray& array) = 0;

        virtual VertexBuffer createVertexBuffer(f32* vertices, u32 size) = 0;
        virtual VertexBuffer createDynamicVertexBuffer(u32 size) = 0; 
        virtual void deleteVertexBuffer(VertexBuffer& buffer) = 0;

        virtual IndexBuffer createIndexBuffer(u32* indices, u32 count) = 0;
        virtual void deleteIndexBuffer(IndexBuffer& buffer) = 0;

        virtual void setVsync(b8 vsync = true) = 0;
        virtual void setClearColor(const Color& color) = 0;

        virtual void setVertexArray(const VertexArray& array) = 0;
        virtual void setVertexBuffer(const VertexBuffer& buffer) = 0;
        virtual void setIndexBuffer(const IndexBuffer& buffer) = 0;

        virtual GraphicsAPI getAPI() const = 0;

        virtual void clear() = 0;
        virtual void makeActive() = 0;  
        virtual void present() = 0;    
    
        static core::Scope<Context> create(GraphicsAPI API, const core::Window& window);
    };
    
} // namespace prime::renderer