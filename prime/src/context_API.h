
#pragma once

#include "prime/defines.h"

namespace prime::renderer {

    class ContextAPI
    {
    public:
        virtual ~ContextAPI() = default;

        virtual void present() = 0;
        virtual void makeActive() = 0;
        virtual void setVsync(b8 vsync) = 0;
    };
    
} // namespace prime::renderer
