
#pragma once

#include "renderer2d.h"

namespace prime::renderer {
    
    class Rect
    {
    public:
        maths::vec2 position;
        maths::vec2 size;

    public:
        Rect() = default;
        Rect(const maths::vec2& pos, const maths::vec2& size);
        Rect(f32 x, f32 y, f32 width, f32 height);

        void render(Renderer2D& renderer);
        void render(Renderer2D& renderer, f32 rotation);
        void render(Renderer2D& renderer, f32 rotation, Anchor anchor);
    };

} // namespace prime::renderer
