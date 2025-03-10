
#pragma once

#include "prime/maths/vec2.h"

namespace prime::maths {

    struct vec3
    {
        f32 x;
        f32 y;
        f32 z;

        vec3();
        vec3(f32 x, f32 y, f32 z);
        vec3(const vec2& vec);
        vec3(const vec2& vec, f32 z);
        vec3(f32 data);

        void add(const vec3& v);
        void sub(const vec3& v);

        void mul(const vec3& v);
        void mul(f32 scaler);

        void div(const vec3& v);
        void div(f32 scaler);

        void normalize();

        static vec3 add(const vec3& lhs, const vec3& rhs);
        static vec3 sub(const vec3& lhs, const vec3& rhs);

        static vec3 mul(const vec3& lhs, const vec3& rhs);
        static vec3 mul(const vec3& lhs, f32 scaler);

        static vec3 div(const vec3& lhs, const vec3& rhs);
        static vec3 div(const vec3& lhs, f32 scaler);

        static f32 lengthSquared(const vec3& vec);
        static f32 length(const vec3& vec);

        static vec3 normalized(const vec3& vec);
        static f32 distanceSquared(const vec3& lhs, const vec3& rhs);
        static f32 distance(const vec3& lhs, const vec3& rhs);

        static b8 equal(const vec3& lhs, const vec3& rhs);
        static b8 notEqual(const vec3& lhs, const vec3& rhs);

        static f32 dot(const vec3& vec1, const vec3& vec2);
        static vec3 cross(const vec3& vec1, const vec3& vec2);
        static str toString(const vec3& vec);
    };
    
} // namespace prime

#ifdef __cplusplus

PRIME_INLINE prime::maths::vec3 operator + (const prime::maths::vec3& lhs, const prime::maths::vec3& rhs)
{
    return prime::maths::vec3::add(lhs, rhs);
}

PRIME_INLINE prime::maths::vec3 operator - (const prime::maths::vec3& lhs, const prime::maths::vec3& rhs)
{
    return prime::maths::vec3::sub(lhs, rhs);
}

PRIME_INLINE prime::maths::vec3 operator / (const prime::maths::vec3& lhs, const prime::maths::vec3& rhs)
{
    return prime::maths::vec3::div(lhs, rhs);
}

PRIME_INLINE prime::maths::vec3 operator / (const prime::maths::vec3& lhs, const f32 scaler)
{
    return prime::maths::vec3::div(lhs, scaler);
}

PRIME_INLINE prime::maths::vec3 operator * (const prime::maths::vec3& lhs, const prime::maths::vec3& rhs)
{
    return prime::maths::vec3::mul(lhs, rhs);
}

PRIME_INLINE prime::maths::vec3 operator * (const prime::maths::vec3& lhs, const f32 scaler)
{
    return prime::maths::vec3::mul(lhs, scaler);
}

PRIME_INLINE prime::maths::vec3& operator += (prime::maths::vec3& lhs, const prime::maths::vec3& rhs)
{
    lhs.add(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec3& operator -= (prime::maths::vec3& lhs, const prime::maths::vec3& rhs)
{
    lhs.sub(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec3& operator /= (prime::maths::vec3& lhs, const prime::maths::vec3& rhs)
{
    lhs.div(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec3& operator /= (prime::maths::vec3& lhs, f32 scaler)
{
    lhs.div(scaler);
    return lhs;
}

PRIME_INLINE prime::maths::vec3& operator *= (prime::maths::vec3& lhs, const prime::maths::vec3& rhs)
{
    lhs.mul(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec3& operator *= (prime::maths::vec3& lhs, f32 scaler)
{
    lhs.mul(scaler);
    return lhs;
}

PRIME_INLINE b8 operator == (const prime::maths::vec3& lhs, const prime::maths::vec3& rhs)
{
    return prime::maths::vec3::equal(lhs, rhs);
}

PRIME_INLINE b8 operator != (const prime::maths::vec3& lhs, const prime::maths::vec3& rhs)
{
    return prime::maths::vec3::notEqual(lhs, rhs);
}

#endif // __cplusplus
