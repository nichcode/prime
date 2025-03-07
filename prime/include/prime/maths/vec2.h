
#pragma once

#include "prime/defines.h"

namespace prime::maths {

    struct vec2
    {
        f32 x;
        f32 y;

        vec2();
        vec2(f32 x, f32 y);
        vec2(f32 data);

        void add(const vec2& v);
        void sub(const vec2& v);

        void mul(const vec2& v);
        void mul(f32 scaler);

        void div(const vec2& v);
        void div(f32 scaler);

        void normalize();

        static vec2 add(const vec2& lhs, const vec2& rhs);
        static vec2 sub(const vec2& lhs, const vec2& rhs);

        static vec2 mul(const vec2& lhs, const vec2& rhs);
        static vec2 mul(const vec2& lhs, f32 scaler);

        static vec2 div(const vec2& lhs, const vec2& rhs);
        static vec2 div(const vec2& lhs, f32 scaler);

        static f32 lengthSquared(const vec2& vec);
        static f32 length(const vec2& vec);

        static vec2 normalized(const vec2& vec);
        static f32 distanceSquared(const vec2& lhs, const vec2& rhs);
        static f32 distance(const vec2& lhs, const vec2& rhs);

        static b8 equal(const vec2& lhs, const vec2& rhs);
        static b8 notEqual(const vec2& lhs, const vec2& rhs);
        static str toString(const vec2& vec);
    };
    
} // namespace prime

#ifdef __cplusplus

PRIME_INLINE prime::maths::vec2 operator + (const prime::maths::vec2& lhs, const prime::maths::vec2& rhs)
{
    return prime::maths::vec2::add(lhs, rhs);
}

PRIME_INLINE prime::maths::vec2 operator - (const prime::maths::vec2& lhs, const prime::maths::vec2& rhs)
{
    return prime::maths::vec2::sub(lhs, rhs);
}

PRIME_INLINE prime::maths::vec2 operator / (const prime::maths::vec2& lhs, const prime::maths::vec2& rhs)
{
    return prime::maths::vec2::div(lhs, rhs);
}

PRIME_INLINE prime::maths::vec2 operator / (const prime::maths::vec2& lhs, const f32 scaler)
{
    return prime::maths::vec2::div(lhs, scaler);
}

PRIME_INLINE prime::maths::vec2 operator * (const prime::maths::vec2& lhs, const prime::maths::vec2& rhs)
{
    return prime::maths::vec2::mul(lhs, rhs);
}

PRIME_INLINE prime::maths::vec2 operator * (const prime::maths::vec2& lhs, const f32 scaler)
{
    return prime::maths::vec2::mul(lhs, scaler);
}

PRIME_INLINE prime::maths::vec2& operator += (prime::maths::vec2& lhs, const prime::maths::vec2& rhs)
{
    lhs.add(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec2& operator -= (prime::maths::vec2& lhs, const prime::maths::vec2& rhs)
{
    lhs.sub(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec2& operator /= (prime::maths::vec2& lhs, const prime::maths::vec2& rhs)
{
    lhs.div(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec2& operator /= (prime::maths::vec2& lhs, f32 scaler)
{
    lhs.div(scaler);
    return lhs;
}

PRIME_INLINE prime::maths::vec2& operator *= (prime::maths::vec2& lhs, const prime::maths::vec2& rhs)
{
    lhs.mul(rhs);
    return lhs;
}

PRIME_INLINE prime::maths::vec2& operator *= (prime::maths::vec2& lhs, f32 scaler)
{
    lhs.mul(scaler);
    return lhs;
}

PRIME_INLINE b8 operator == (const prime::maths::vec2& lhs, const prime::maths::vec2& rhs)
{
    return prime::maths::vec2::equal(lhs, rhs);
}

PRIME_INLINE b8 operator != (const prime::maths::vec2& lhs, const prime::maths::vec2& rhs)
{
    return prime::maths::vec2::notEqual(lhs, rhs);
}

#endif // __cplusplus
