
#pragma once

#include "defines.h"

namespace prime {

    struct vec2
    {
        f32 x;
        f32 y;

        vec2(f32 x, f32 y)
        {
            this->x = x;
            this->y = y;
        }
    };

    struct vec3
    {
        f32 x;
        f32 y;
        f32 z;

        vec3(f32 x, f32 y, f32 z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

    struct vec4
    {
        f32 x;
        f32 y;
        f32 z;
        f32 w;

        vec4(f32 x, f32 y, f32 z, f32 w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
    };

    struct mat4
    {
        f32 data[16];

        mat4()
        {
            for (u32 x = 0; x < 16; x++) {
                data[x] = 0.0f;
            }   
        }
    };
    
} // namespace prime
