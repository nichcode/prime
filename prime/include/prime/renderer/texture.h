
#pragma once

#include "prime/defines.h"

namespace prime::renderer {

    class Texture
    {
    public:
        virtual ~Texture() {} 

        virtual void bind(u32 slot = 0) const = 0;
        virtual void unBind() const = 0;

        virtual void bindTarget() const = 0;
        virtual void unBindTarget() const = 0;

        virtual u32 getWidth() const  = 0;
        virtual u32 getHeight() const = 0;
        virtual const str& getPath() const = 0;
    };
    
} // namespace prime::renderer
