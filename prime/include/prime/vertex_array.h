
#pragma once

#include "buffers.h"

namespace prime {

    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void
        submit(const VertexBuffer* vertex_buffer) = 0;

        virtual u32 
        getID() const = 0;
    };
    
    
} // namespace prime
