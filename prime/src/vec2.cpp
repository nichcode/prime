
#include "prime/maths/vec2.h"
#include "prime/maths/maths.h"
#include "prime/core/fmt.h"

namespace prime::maths {

    vec2::vec2()
    {
        x = 0.0f;
        y = 0.0f;
    }
    
    vec2::vec2(f32 x, f32 y)
    {
        this->x = x;
        this->y = y;
    }
    
    vec2::vec2(f32 data)
    {
        this->x = data;
        this->y = data;
    }

    void vec2::add(const vec2& v)
    {
        this->x += v.x;
        this->y += v.y;
    }

    void vec2::sub(const vec2& v)
    {
        this->x -= v.x;
        this->y -= v.y;
    }

    void vec2::mul(const vec2& v)
    {
        this->x *= v.x;
        this->y *= v.y;
    }

    void vec2::mul(f32 scaler)
    {
        this->x *= scaler;
        this->y *= scaler;
    }

    void vec2::div(const vec2& v)
    {
        this->x /= v.x;
        this->y /= v.y;
    }

    void vec2::div(f32 scaler)
    {
        this->x /= scaler;
        this->y /= scaler;
    }

    void vec2::normalize()
    {
        const f32 length = sqrt(x * x + y * y);
        x /= length;
        y /= length;
    }

    vec2 vec2::add(const vec2& lhs, const vec2& rhs)
    {
        return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    vec2 vec2::sub(const vec2& lhs, const vec2& rhs)
    {
        return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    vec2 vec2::mul(const vec2& lhs, const vec2& rhs)
    {
        return vec2(lhs.x * rhs.x, lhs.y * rhs.y);
    }

    vec2 vec2::mul(const vec2& lhs, f32 scaler)
    {
        return vec2(lhs.x * scaler, lhs.y * scaler);
    }

    vec2 vec2::div(const vec2& lhs, const vec2& rhs)
    {
        return vec2(lhs.x / rhs.x, lhs.y / rhs.y);
    }

    vec2 vec2::div(const vec2& lhs, f32 scaler)
    {
        return vec2(lhs.x / scaler, lhs.y / scaler);
    }

    f32 vec2::lengthSquared(const vec2& vec)
    {
        return vec.x * vec.x + vec.y * vec.y;
    }

    f32 vec2::length(const vec2& vec)
    {
        return sqrt(vec.x * vec.x + vec.y * vec.y);
    }

    vec2 vec2::normalized(const vec2& vec)
    {
        vec2 v = vec;
        const f32 length = vec2::length(vec);
        v.x /= length;
        v.y /= length;
        return v;
    }

    f32 vec2::distanceSquared(const vec2& lhs, const vec2& rhs)
    {
        vec2 vec(lhs.x - rhs.x, lhs.y - rhs.y);
        return lengthSquared(vec);
    }

    f32 vec2::distance(const vec2& lhs, const vec2& rhs)
    {
        vec2 vec(lhs.x - rhs.x, lhs.y - rhs.y);
        return length(vec);
    }

    b8 vec2::equal(const vec2& lhs, const vec2& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    b8 vec2::notEqual(const vec2& lhs, const vec2& rhs)
    {
        return lhs.x != rhs.x && lhs.y != rhs.y;
    }

    str vec2::toString(const vec2& vec)
    {
        return core::format("vec2(%.2f, %.2f)", vec.x, vec.y);
    }
    
} // namespace priem::maths
