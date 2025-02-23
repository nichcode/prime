
#pragma once

#include "window.h"
#include "color.h"

namespace prime {

    enum class BufferType
    {
        Vertex,
        Index
    };

    enum class BufferUsage
    {
        DynamicDraw,
        StaticDraw
    };

    struct BufferDesc
    {
        BufferType type = BufferType::Vertex;
        BufferUsage usage = BufferUsage::StaticDraw;
        void* data = nullptr;
        u32 size = 0;
    };

    class Buffer
    {
    public:
        virtual ~Buffer() {};

        virtual void
        setData(const void* data, u32 size) = 0;
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

        virtual Buffer*
        createBuffer(const BufferDesc& desc) = 0;

        virtual void
        destroyBuffer(Buffer* buffer) = 0;
    };
    
} // namespace prime
