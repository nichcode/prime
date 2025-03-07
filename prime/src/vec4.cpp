
#include "prime/maths/vec4.h"
#include "prime/maths/maths.h"
#include "prime/core/fmt.h"

namespace prime::maths {

    vec4::vec4()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 0.0f;
    }
    
    vec4::vec4(f32 x, f32 y, f32 z, f32 w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    vec4::vec4(const vec2& vec)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = 0.0f;
        this->w = 0.0f;
    }

    vec4::vec4(const vec3& vec)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        this->w = 0.0f;
    }

    vec4::vec4(const vec3& vec, f32 w)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
        this->w = w;
    }
    
    vec4::vec4(f32 data)
    {
        this->x = data;
        this->y = data;
        this->z = data;
        this->w = data;
    }

    void vec4::add(const vec4& v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        this->w += v.w;
    }

    void vec4::sub(const vec4& v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        this->w -= v.w;
    }

    void vec4::mul(const vec4& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        this->w *= v.w;
    }

    void vec4::mul(f32 scaler)
    {
        this->x *= scaler;
        this->y *= scaler;
        this->z *= scaler;
        this->w *= scaler;
    }

    void vec4::div(const vec4& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        this->w /= v.w;
    }

    void vec4::div(f32 scaler)
    {
        this->x /= scaler;
        this->y /= scaler;
        this->z /= scaler;
        this->w /= scaler;
    }

    void vec4::normalize()
    {
        const f32 length = sqrt(x * x + y * y + z * z + w * w);
        x /= length;
        y /= length;
        z /= length;
        w /= length;
    }

    vec4 vec4::add(const vec4& lhs, const vec4& rhs)
    {
        return vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
    }

    vec4 vec4::sub(const vec4& lhs, const vec4& rhs)
    {
        return vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
    }

    vec4 vec4::mul(const vec4& lhs, const vec4& rhs)
    {
        return vec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
    }

    vec4 vec4::mul(const vec4& lhs, f32 scaler)
    {
        return vec4(lhs.x * scaler, lhs.y * scaler, lhs.z * scaler, lhs.w * scaler);
    }

    vec4 vec4::div(const vec4& lhs, const vec4& rhs)
    {
        return vec4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
    }

    vec4 vec4::div(const vec4& lhs, f32 scaler)
    {
        return vec4(lhs.x / scaler, lhs.y / scaler, lhs.z / scaler, lhs.w / scaler);
    }

    f32 vec4::lengthSquared(const vec4& vec)
    {
        return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
    }

    f32 vec4::length(const vec4& vec)
    {
        return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
    }

    vec4 vec4::normalized(const vec4& vec)
    {
        vec4 v = vec;
        const f32 length = vec4::length(vec);
        v.x /= length;
        v.y /= length;
        v.z /= length;
        v.w /= length;
        return v;
    }

    f32 vec4::distanceSquared(const vec4& lhs, const vec4& rhs)
    {
        vec4 vec(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
        return lengthSquared(vec);
    }

    f32 vec4::distance(const vec4& lhs, const vec4& rhs)
    {
        vec4 vec(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
        return length(vec);
    }

    b8 vec4::equal(const vec4& lhs, const vec4& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
    }

    b8 vec4::notEqual(const vec4& lhs, const vec4& rhs)
    {
        return lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z && lhs.w != rhs.w;
    }

    str vec4::toString(const vec4& vec)
    {
        return core::format("vec4(%.2f, %.2f, %.2f, %.2f)", vec.x, vec.y, vec.z, vec.w);
    }
    
} // namespace priem::maths
