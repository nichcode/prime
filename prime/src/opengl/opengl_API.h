
#pragma once

#include "prime/defines.h"
#include "glad/glad.h"

namespace prime {

    struct VertexArrayHandle
    {
        u32 id = 0;
    };

    struct VertexBufferHandle
    {
        u32 id = 0;
    };

    struct IndexBufferHandle
    {
        u32 id = 0;
    };

    struct ShaderHandle
    {
        u32 id = 0;
    };

    struct TextureHandle
    {
        u32 id = 0;
        u32 buffer = 0;
    };
    
} // namespace prime
