
#include "prime/renderer/rect.h"

namespace prime::renderer {

    Rect::Rect(const maths::vec2& pos, const maths::vec2& size)
    {
        this->position = pos;
        this->size = size;
    }

    Rect::Rect(f32 x, f32 y, f32 width, f32 height)
    {
        position.x = x;
        position.y = y;
        size.x = width;
        size.y = height;
    }

    void Rect::render(Renderer2D& renderer)
    {
        renderer.draw(position, size);
    }

    void Rect::render(Renderer2D& renderer, f32 rotation)
    {
        renderer.draw(position, size, rotation);
    }
    
    void Rect::render(Renderer2D& renderer, f32 rotation, Anchor anchor)
    {
        renderer.draw(position, size, rotation, anchor);
    }
    
} // namespace prime::renderer
