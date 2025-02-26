
#pragma once

#include "window.h"
#include "color.h"
#include "vertex_array.h"
#include "shader.h"
#include "rect.h"
#include "textures.h"
#include "utils.h"

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
        present() = 0;    
        
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

        virtual void
        setVertexArray(const Ref<VertexArray>& vertex_array) = 0;

        virtual void
        setVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) = 0;

        virtual void
        setIndexBuffer(const Ref<IndexBuffer>& index_buffer) = 0;

        virtual void
        setShader(const Ref<Shader>& shader) = 0;

        virtual void
        setTexture(const Ref<Texture>& texture, u32 slot = 0) = 0;

        virtual void
        setRenderTarget(const Ref<Texture>& texture) = 0;

        virtual void
        drawElements(DrawMode mode, u32 count) = 0;
    };
    
} // namespace prime
