
#pragma once

#include "prime/buffer.h"
#include "glad/glad.h"

namespace prime {

    PINLINE static i32 
    getBufferType(BufferType type)
    {
        switch (type)
        {
            case BufferType::Vertex: {
                return GL_ARRAY_BUFFER;
            }
            break;

            case BufferType::Index: {
                return GL_ELEMENT_ARRAY_BUFFER;
            }
            break;
        }
        return 0;
    }
    
} // namespace prime
