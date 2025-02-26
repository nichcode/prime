
#pragma once

#include "defines.h"

namespace prime {

    class Texture2D
    {
    public:
        virtual ~Texture2D() {}

        virtual u32 
        getWidth() const = 0;

        virtual u32 
        getHeight() const = 0;

        virtual u32 
        getID() const = 0;

        virtual str 
        getPath() const = 0;

        virtual void* 
        getHandle() const = 0;
    };
    
} // namespace prime
