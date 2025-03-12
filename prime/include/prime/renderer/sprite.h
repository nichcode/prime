
#pragma once

#include "rect.h"

namespace prime::renderer {

    class Sprite
    {
    public:
        maths::vec2 position;
        maths::vec2 size;
        Texture* texture;

    public:
        Sprite() : texture(nullptr) {}
        Sprite(const maths::vec2& pos, const maths::vec2& size, Texture* texture);
        Sprite(f32 x, f32 y, f32 width, f32 height, Texture* texture);

        const Rect getRect() { return Rect{ position, size }; }

        void render(Renderer2D& renderer);
        void render(Renderer2D& renderer, b8 flip_x, b8 flip_y);
        void render(Renderer2D& renderer, f32 rotation);

        void render(Renderer2D& renderer, f32 rotation, Anchor anchor);
        void render(Renderer2D& renderer, f32 rotation, Anchor anchor, b8 flip_x, b8 flip_y);
    };
    
} // namespace prime::renderer
