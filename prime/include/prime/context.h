
#pragma once

#include "window.h"
#include "color.h"

namespace prime {

    class Context
    {
    public:
        virtual ~Context() {};

        virtual void
        swapbuffers() = 0;    
        
        virtual void
        makeActive() = 0;

        virtual void
        setClearColor(const Color& color) = 0;

        virtual void
        clear() = 0;

    };
    
} // namespace prime
