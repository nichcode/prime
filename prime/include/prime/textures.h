
#pragma once

#include "defines.h"

namespace prime {

    struct TextureHandle;

    enum class TextureUsage
    {
        None,
        RenderTarget
    };

    class Texture
    {
    public:
        virtual ~Texture() {}

        virtual void
        resize(u32 width, u32 height) = 0;

        virtual u32 
        getWidth() const = 0;

        virtual u32 
        getHeight() const = 0;

        virtual TextureUsage 
        getUsage() const = 0;

        virtual str 
        getPath() const = 0;

        virtual TextureHandle* 
        getHandle() const = 0;
    };
    
} // namespace prime
