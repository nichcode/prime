
#pragma once

#include "prime/defines.h"

namespace prime::renderer {

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void setData(const void* data, u32 size) = 0;
    
        virtual void bind() const = 0;
        virtual void unBind() const = 0;
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual u32 getCount() const = 0;

        virtual void bind() const = 0;
        virtual void unBind() const = 0;
    };

    class UniformBuffer
    {
    public:
        virtual ~UniformBuffer() {}

        virtual void setData(const void* data, u32 size) = 0;

        virtual void bind() const = 0;
        virtual void unBind() const = 0;
    };

} // namespace prime::renderer
