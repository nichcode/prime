
#pragma once

#include "device.h"

namespace prime {

    class Renderer2D
    {
    public:
        static void 
        init(Ref<Device>& device);

        static void
        destroy();

        static void
        drawRect(const Rect& rect, f32 layer = 0.0f);

        static void
        drawRect(const Rect& rect, const Color& color, f32 layer = 0.0f);

        static void
        begin();

        static void
        end();
    };
    
} // namespace prime
