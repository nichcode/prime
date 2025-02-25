
#pragma once

#include "window.h"
#include "color.h"
#include "vertex_array.h"
#include "shader.h"
#include "rect.h"

namespace prime {

    enum DrawMode
    {
        Triangles,
        Lines
    };

    class Context
    {
    public:
        virtual ~Context() {};

        virtual void
        swapbuffers() = 0;    
        
        virtual void
        makeActive() = 0;

        virtual void
        setClearColor(const Color& color) = 0;

        virtual void
        clear() = 0;

        virtual void
        setViewport(const Rect& viewport) = 0;

        virtual const Rect&
        getViewport() const = 0;

        virtual VertexArray*
        createVertexArray() = 0;

        virtual void
        destroyVertexArray(VertexArray* vertex_array) = 0;

        virtual VertexBuffer*
        createDynamicVertexBuffer(u32 size) = 0;

        virtual VertexBuffer*
        createStaticVertexBuffer(f32* vertices, u32 size) = 0;

        virtual void
        destroyVertexBuffer(VertexBuffer* vertex_buffer) = 0;

        virtual IndexBuffer*
        createIndexBuffer(u32* indices, u32 count)  = 0;

        virtual void
        destroyIndexBuffer(IndexBuffer* index_buffer) = 0;

        virtual Shader*
        createShader(const ShaderDesc& desc) = 0;

        virtual void
        destroyShader(Shader* shader) = 0;

        virtual void
        setVertexArray(VertexArray* vertex_array) = 0;

        virtual void
        setVertexBuffer(VertexBuffer* vertex_buffer) = 0;

        virtual void
        setIndexBuffer(IndexBuffer* index_buffer) = 0;

        virtual void
        setShader(Shader* shader) = 0;

        virtual void
        drawElements(DrawMode mode, u32 count) = 0;
    };
    
} // namespace prime
