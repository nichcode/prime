
#pragma once

#include "buffers.h"
#include "utils.h"

namespace prime {

    class VertexArrayHandle;

    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void
        submit(const Ref<VertexBuffer>& vertex_buffer) = 0;

        virtual VertexArrayHandle* 
        getHandle() const = 0;
    };
    
    
} // namespace prime
