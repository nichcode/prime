
#pragma once

#include "rect.h"
#include "texture.h"

namespace prime::renderer {

    class Sprite
    {
    private:
        Rect rect;
        core::Ref<Texture> texture;

    public:
        Sprite() = default;
        Sprite(const maths::vec2& pos, const maths::vec2& size, core::Ref<Texture>& texture);
        Sprite(f32 x, f32 y, f32 width, f32 height, core::Ref<Texture>& texture);

        Rect& getRect() { return rect; }

        void render(Renderer2D& renderer);
        void render(Renderer2D& renderer, b8 flip_x, b8 flip_y);
        void render(Renderer2D& renderer, f32 rotation);

        void render(Renderer2D& renderer, f32 rotation, Anchor anchor);
        void render(Renderer2D& renderer, f32 rotation, Anchor anchor, b8 flip_x, b8 flip_y);
    };
    
} // namespace prime::renderer
