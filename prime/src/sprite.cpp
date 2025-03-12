
#include "prime/renderer/sprite.h"

namespace prime::renderer {

    Sprite::Sprite(const maths::vec2& pos, const maths::vec2& size, Texture* texture)
    {
        this->position = pos;
        this->size = size;
        this->texture = texture;
    }
    
    Sprite::Sprite(f32 x, f32 y, f32 width, f32 height, Texture* texture)
    {
        this->position.x = x;
        this->position.y = y;
        this->size.x = width;
        this->size.y = height;
        this->texture = texture;
    }

    void Sprite::render(Renderer2D& renderer)
    {
        renderer.draw(position, size, texture);
    }

    void Sprite::render(Renderer2D& renderer, b8 flip_x, b8 flip_y)
    {
        renderer.draw(position, size, texture, flip_x, flip_y);
    }

    void Sprite::render(Renderer2D& renderer, f32 rotation)
    {
        renderer.draw(position, size, texture, rotation);
    }

    void Sprite::render(Renderer2D& renderer, f32 rotation, Anchor anchor)
    {
        renderer.draw(position, size, texture, rotation, anchor);
    }

    void Sprite::render(Renderer2D& renderer, f32 rotation, Anchor anchor, b8 flip_x, b8 flip_y)
    {
        renderer.draw(position, size, texture, flip_x, flip_y, rotation, anchor);
    }
    
} // namespace prime::renderer
