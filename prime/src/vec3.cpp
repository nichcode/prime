
#include "prime/maths/vec3.h"
#include "prime/maths/maths.h"
#include "prime/core/fmt.h"

namespace prime::maths {

    vec3::vec3()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }
    
    vec3::vec3(f32 x, f32 y, f32 z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    vec3::vec3(const vec2& vec)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = 0.0f;
    }

    vec3::vec3(const vec2& vec, f32 z)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = z;
    }
    
    vec3::vec3(f32 data)
    {
        this->x = data;
        this->y = data;
        this->z = data;
    }

    void vec3::add(const vec3& v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
    }

    void vec3::sub(const vec3& v)
    {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
    }

    void vec3::mul(const vec3& v)
    {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
    }

    void vec3::mul(f32 scaler)
    {
        this->x *= scaler;
        this->y *= scaler;
        this->z *= scaler;
    }

    void vec3::div(const vec3& v)
    {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
    }

    void vec3::div(f32 scaler)
    {
        this->x /= scaler;
        this->y /= scaler;
        this->z /= scaler;
    }

    void vec3::normalize()
    {
        const f32 length = sqrt(x * x + y * y + z * z);
        x /= length;
        y /= length;
        z /= length;
    }

    vec3 vec3::add(const vec3& lhs, const vec3& rhs)
    {
        return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    vec3 vec3::sub(const vec3& lhs, const vec3& rhs)
    {
        return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

    vec3 vec3::mul(const vec3& lhs, const vec3& rhs)
    {
        return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
    }

    vec3 vec3::mul(const vec3& lhs, f32 scaler)
    {
        return vec3(lhs.x * scaler, lhs.y * scaler, lhs.z * scaler);
    }

    vec3 vec3::div(const vec3& lhs, const vec3& rhs)
    {
        return vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
    }

    vec3 vec3::div(const vec3& lhs, f32 scaler)
    {
        return vec3(lhs.x / scaler, lhs.y / scaler, lhs.z / scaler);
    }

    f32 vec3::lengthSquared(const vec3& vec)
    {
        return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
    }

    f32 vec3::length(const vec3& vec)
    {
        return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    }

    vec3 vec3::normalized(const vec3& vec)
    {
        vec3 v = vec;
        const f32 length = vec3::length(vec);
        v.x /= length;
        v.y /= length;
        v.z /= length;
        return v;
    }

    f32 vec3::distanceSquared(const vec3& lhs, const vec3& rhs)
    {
        vec3 vec(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        return lengthSquared(vec);
    }

    f32 vec3::distance(const vec3& lhs, const vec3& rhs)
    {
        vec3 vec(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        return length(vec);
    }

    b8 vec3::equal(const vec3& lhs, const vec3& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }

    b8 vec3::notEqual(const vec3& lhs, const vec3& rhs)
    {
        return lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z;
    }

    f32 vec3::dot(const vec3& vec1, const vec3& vec2)
    {
        f32 p = 0;
        p += vec1.x * vec2.x;
        p += vec1.y * vec2.y;
        p += vec1.z * vec2.z;
        return p;
    }

    vec3 vec3::cross(const vec3& vec1, const vec3& vec2)
    {
        return vec3(
                vec1.y * vec2.z - vec1.z * vec2.y,
                vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x
            );
    }

    str vec3::toString(const vec3& vec)
    {
        return core::format("vec3(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
    }
    
} // namespace priem::maths
