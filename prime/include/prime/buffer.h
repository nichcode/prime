
#pragma once

#include "defines.h"

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

        virtual BufferType
        getType() const = 0;

        virtual BufferUsage
        getUsage() const = 0;

        virtual u32 getID() const = 0;
        virtual void* getHandle() const = 0;
    };
    
} // namespace prime
