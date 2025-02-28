
#pragma once

#include "layout.h"

namespace prime {

    struct VertexBufferHandle;
    struct IndexBufferHandle;
    struct UniformBufferHandle;

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void
        setData(const void* data, u32 size) = 0;

        virtual void 
        setLayout(const Layout& layout) = 0;

        virtual VertexBufferHandle*
        getHandle() const = 0;

		virtual const 
        Layout& getLayout() const = 0;
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual u32 
        getCount() const = 0;

        virtual IndexBufferHandle*
        getHandle() const = 0;
    };

    class UniformBuffer
    {
    public:
        virtual ~UniformBuffer() {}

        virtual void
        setData(const void* data, u32 size) = 0;

        virtual UniformBufferHandle*
        getHandle() const = 0;
    };
    
} // namespace prime
