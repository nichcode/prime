
#pragma once

#include "prime/defines.h"

namespace prime::renderer {

    struct Color
    {
        f32 r;
        f32 b;
        f32 g;
        f32 a;

        Color()
        {
            this->r = 0.0f;
            this->b = 0.0f;
            this->g = 0.0f;
            this->a = 1.0f;
        }

        Color(f32 value)
        {
            this->r = value;
            this->b = value;
            this->g = value;
            this->a = 1.0f;
        }

        Color(f32 r, f32 g, f32 b, f32 a)
        {
            this->r = r;
            this->b = g;
            this->g = b;
            this->a = a;
        }

        Color(u32 r, u32 g, u32 b, u32 a)
        {
            this->r = (f32)r / 255.0f;
            this->b = (f32)g / 255.0f;
            this->g = (f32)b / 255.0f;
            this->a = (f32)a / 255.0f;
        }
    };

} // namespace prime

#define PRIME_COLOR_RED               prime::renderer::Color(1.0f, 0.0f, 0.0f, 1.0f)
#define PRIME_COLOR_GREEN             prime::renderer::Color(0.0f, 1.0f, 0.0f, 1.0f)
#define PRIME_COLOR_BLUE              prime::renderer::Color(0.0f, 0.0f, 1.0f, 1.0f)
#define PRIME_COLOR_WHITE             prime::renderer::Color(1.0f, 1.0f, 1.0f, 1.0f)
#define PRIME_COLOR_BLACK             prime::renderer::Color(0.0f, 0.0f, 0.0f, 1.0f)