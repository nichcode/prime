
#pragma once

#include "window.h"
#include "color.h"
#include "buffer.h"
#include "layout.h"
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

        virtual Buffer*
        createBuffer(const BufferDesc& desc) = 0;

        virtual void
        destroyBuffer(Buffer* buffer) = 0;

        virtual Layout*
        createLayout() = 0;

        virtual void
        destroyLayout(Layout* layout) = 0;

        virtual Shader*
        createShader(const ShaderDesc& desc) = 0;

        virtual void
        destroyShader(Shader* shader) = 0;

        virtual void
        setLayout(Layout* layout, b8 submit) = 0;

        virtual void
        setBuffer(Buffer* buffer) = 0;

        virtual void
        setShader(Shader* shader) = 0;

        virtual void
        drawElements(DrawMode mode, u32 count) = 0;
    };
    
} // namespace prime
