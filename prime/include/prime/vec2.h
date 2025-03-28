
#pragma once

#include "prime/maths.h"
#include "prime/string.h"

struct primeVec2
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

PRIME_INLINE primeVec2 primeCreateVec2(f32 x, f32 y)
{
    primeVec2 v;
    v.x = x;
    v.y = y;
    return v;
}

PRIME_INLINE primeVec2 primeAddVec2(const primeVec2 a, const primeVec2 b)
{
    return primeCreateVec2(a.x + b.x, a.y + b.y);
}

PRIME_INLINE primeVec2 primeSubVec2(const primeVec2 a, const primeVec2 b)
{
    return primeCreateVec2(a.x - b.x, a.y - b.y);
}

PRIME_INLINE primeVec2 primeDivVec2(const primeVec2 a, const primeVec2 b)
{
    return primeCreateVec2(a.x / b.x, a.y / b.y);
}

PRIME_INLINE primeVec2 primeDivVec2_s(const primeVec2 a, f32 scaler)
{
    return primeCreateVec2(a.x / scaler, a.y / scaler);
}

PRIME_INLINE primeVec2 primeMulVec2(const primeVec2 a, const primeVec2 b)
{
    return primeCreateVec2(a.x * b.x, a.y * b.y);
}

PRIME_INLINE primeVec2 primeMulVec2_s(const primeVec2 a, f32 scaler)
{
    return primeCreateVec2(a.x * scaler, a.y * scaler);
}

PRIME_INLINE f32 primeVec2Length(const primeVec2 vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

PRIME_INLINE f32 primeVec2Length_s(const primeVec2 vec)
{
    return primeSqrt(vec.x * vec.x + vec.y * vec.y);
}

PRIME_INLINE f32 primeVec2Distance(const primeVec2 a, const primeVec2 b)
{
    primeVec2 vec = primeCreateVec2(a.x - b.x, a.y - b.y);
    return primeVec2Length(vec);
}

PRIME_INLINE f32 primeVec2Distance_s(const primeVec2 a, const primeVec2 b)
{
    primeVec2 vec = primeCreateVec2(a.x - b.x, a.y - b.y);
    return primeVec2Length_s(vec);
}

PRIME_INLINE primeVec2 primeVec2Normalized(const primeVec2 vec)
{
    primeVec2 v = vec;
    const f32 length = primeVec2Length(vec);
    v.x /= length;
    v.y /= length;
    return v;
}

PRIME_INLINE b8 primeVec2Equal(const primeVec2 a, const primeVec2 b)
{
    return a.x == b.x && a.y == b.y;
}

PRIME_INLINE char* primeVec2ToString(primeVec2 vec)
{
    return primeFormat("vec2(%.2f, %.2f)", vec.x, vec.y);
}

#ifdef __cplusplus

// vec2
PRIME_INLINE primeVec2 operator + (const primeVec2& a, const primeVec2& b)
{
    return primeAddVec2(a, b);
}

PRIME_INLINE primeVec2 operator - (const primeVec2& a, const primeVec2& b)
{
    return primeSubVec2(a, b);
}

PRIME_INLINE primeVec2 operator / (const primeVec2& a, const primeVec2& b)
{
    return primeDivVec2(a, b);
}

PRIME_INLINE primeVec2 operator / (const primeVec2& a, const f32 scaler)
{
    return primeDivVec2_s(a, scaler);
}

PRIME_INLINE primeVec2 operator * (const primeVec2& a, const primeVec2& b)
{
    return primeMulVec2(a, b);
}

PRIME_INLINE primeVec2 operator * (const primeVec2& a, const f32 scaler)
{
    return primeMulVec2_s(a, scaler);
}

PRIME_INLINE primeVec2& operator += (primeVec2& a, const primeVec2& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

PRIME_INLINE primeVec2& operator -= (primeVec2& a, const primeVec2& b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

PRIME_INLINE primeVec2& operator /= (primeVec2& a, const primeVec2& b)
{
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

PRIME_INLINE primeVec2& operator /= (primeVec2& a, f32 scaler)
{
    a.x /= scaler;
    a.y /= scaler;
    return a;
}

PRIME_INLINE primeVec2& operator *= (primeVec2& a, const primeVec2& b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

PRIME_INLINE primeVec2& operator *= (primeVec2& a, f32 scaler)
{
    a.x *= scaler;
    a.y *= scaler;
    return a;
}

PRIME_INLINE b8 operator == (const primeVec2& a, const primeVec2& b)
{
    return primeVec2Equal(a, b);
}

#endif // __cplusplus