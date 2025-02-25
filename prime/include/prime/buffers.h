
#pragma once

#include "layout.h"

namespace prime {

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {};

        virtual void
        setData(const void* data, u32 size) = 0;

        virtual void 
        setLayout(const Layout& layout) = 0;

        virtual void* 
        getHandle() const = 0;

        virtual u32 
        getID() const = 0;

		virtual const 
        Layout& getLayout() const = 0;
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {};

        virtual void* 
        getHandle() const = 0;

        virtual u32 
        getID() const = 0;

        virtual u32 
        getCount() const = 0;
    };
    
} // namespace prime
