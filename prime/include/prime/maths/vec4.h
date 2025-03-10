
#pragma once

#include "prime/maths/vec3.h"

namespace prime::maths {

    struct vec4
    {
        f32 x;
        f32 y;
        f32 z;
        f32 w;

        vec4();
        vec4(f32 x, f32 y, f32 z, f32 w);
        vec4(const vec2& vec);
        vec4(const vec3& vec);
        vec4(const vec3& vec, f32 w);
        vec4(f32 data);

        void add(const vec4& v);
        void sub(const vec4& v);

        void mul(const vec4& v);
        void mul(f32 scaler);

        void div(const vec4& v);
        void div(f32 scaler);

        void normalize();

        static vec4 add(const vec4& lhs, const vec4& rhs);
        static vec4 sub(const vec4& lhs, const vec4& rhs);

        static vec4 mul(const vec4& lhs, const vec4& rhs);
        static vec4 mul(const vec4& lhs, f32 scaler);

        static vec4 div(const vec4& lhs, const vec4& rhs);
        static vec4 div(const vec4& lhs, f32 scaler);

        static f32 lengthSquared(const vec4& vec);
        static f32 length(const vec4& vec);

        static vec4 normalized(const vec4& vec);
        static f32 distanceSquared(const vec4& lhs, const vec4& rhs);
        static f32 distance(const vec4& lhs, const vec4& rhs);

        static b8 equal(const vec4& lhs, const vec4& rhs);
        static b8 notEqual(const vec4& lhs, const vec4& rhs);
        static str toString(const vec4& vec);
    };
    
} // namespace prime

#ifdef __cplusplus

PRIME_INLINE prime::maths::vec4 operator + (const prime::maths::vec4& lhs, const prime::maths::vec4& rhs)
{
    return prime::maths::vec4::add(lhs, rhs);
}

PRIME_INLINE prime::maths::vec4 operator - (const prime::maths::vec4& lhs, const prime::maths::vec4& rhs)
{
    return prime::maths::vec4::sub(lhs, rhs);
}

PRIME_INLINE prime::maths::vec4 operator / (const prime::maths::vec4& lhs, const prime::maths::vec4& rhs)
{
    return prime::maths::vec4::div(lhs, rhs);
}

PRIME_INLINE prime::maths::vec4 operator / (const prime::maths::vec4& lhs, const f32 scaler)
{
    return prime::maths::vec4::div(lhs, scaler);
}

PRIME_INLINE prime::maths::vec4 operator * (const prime::maths::vec4& lhs, const prime::maths::vec4& rhs)
{
    return prime::maths::vec4::mul(lhs, rhs);
}

PRIME_INLINE prime::maths::vec4 operator * (const prime::maths::vec4& lhs, const f32 scaler)
{
    return prime::maths::vec4::mul(lhs, scaler);
}

PRIME_INLINE prime::maths::vec4& operator += (prime::maths::vec4& lhs, const prime::maths::vec4& rhs)
{
    lhs.add(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec4& operator -= (prime::maths::vec4& lhs, const prime::maths::vec4& rhs)
{
    lhs.sub(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec4& operator /= (prime::maths::vec4& lhs, const prime::maths::vec4& rhs)
{
    lhs.div(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec4& operator /= (prime::maths::vec4& lhs, f32 scaler)
{
    lhs.div(scaler);
    return lhs;
}

PRIME_INLINE prime::maths::vec4& operator *= (prime::maths::vec4& lhs, const prime::maths::vec4& rhs)
{
    lhs.mul(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec4& operator *= (prime::maths::vec4& lhs, f32 scaler)
{
    lhs.mul(scaler);
    return lhs;
}

PRIME_INLINE b8 operator == (const prime::maths::vec4& lhs, const prime::maths::vec4& rhs)
{
    return prime::maths::vec4::equal(lhs, rhs);
}

PRIME_INLINE b8 operator != (const prime::maths::vec4& lhs, const prime::maths::vec4& rhs)
{
    return prime::maths::vec4::notEqual(lhs, rhs);
}

#endif // __cplusplus
