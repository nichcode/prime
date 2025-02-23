
#pragma once

#include "defines.h"

namespace prime {

    struct Rect
    {
        f32 x;
        f32 y;
        f32 width;
        f32 height;

        Rect()
        {
            x = 0.0f;
            y = 0.0f;
            width = 0.0f;
            height = 0.0f;
        }

        Rect(f32 x, f32 y, f32 width, f32 height)
        {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }
    };
    
} // namespace prime