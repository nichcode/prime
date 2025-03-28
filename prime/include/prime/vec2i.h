
#pragma once

#include "prime/maths.h"
#include "prime/string.h"

struct primeVec2i
{
    i32 x = 0;
    i32 y = 0;
};

PRIME_INLINE primeVec2i primeCreateVec2i(i32 x, i32 y)
{
    primeVec2i v;
    v.x = x;
    v.y = y;
    return v;
}

PRIME_INLINE primeVec2i primeAddVec2i(const primeVec2i a, const primeVec2i b)
{
    return primeCreateVec2i(a.x + b.x, a.y + b.y);
}

PRIME_INLINE primeVec2i primeSubVec2i(const primeVec2i a, const primeVec2i b)
{
    return primeCreateVec2i(a.x - b.x, a.y - b.y);
}

PRIME_INLINE primeVec2i primeDivVec2i(const primeVec2i a, const primeVec2i b)
{
    return primeCreateVec2i(a.x / b.x, a.y / b.y);
}

PRIME_INLINE primeVec2i primeDivVec2i_s(const primeVec2i a, i32 scaler)
{
    return primeCreateVec2i(a.x / scaler, a.y / scaler);
}

PRIME_INLINE primeVec2i primeMulVec2i(const primeVec2i a, const primeVec2i b)
{
    return primeCreateVec2i(a.x * b.x, a.y * b.y);
}

PRIME_INLINE primeVec2i primeMulVec2i_s(const primeVec2i a, i32 scaler)
{
    return primeCreateVec2i(a.x * scaler, a.y * scaler);
}

PRIME_INLINE b8 primeVec2iEqual(const primeVec2i a, const primeVec2i b)
{
    return a.x == b.x && a.y == b.y;
}

PRIME_INLINE char* primeVec2iToString(primeVec2i vec)
{
    return primeFormat("vec2i(%i, %i)", vec.x, vec.y);
}

#ifdef __cplusplus

PRIME_INLINE primeVec2i operator + (const primeVec2i& a, const primeVec2i& b)
{
    return primeAddVec2i(a, b);
}

PRIME_INLINE primeVec2i operator - (const primeVec2i& a, const primeVec2i& b)
{
    return primeSubVec2i(a, b);
}

PRIME_INLINE primeVec2i operator / (const primeVec2i& a, const primeVec2i& b)
{
    return primeDivVec2i(a, b);
}

PRIME_INLINE primeVec2i operator / (const primeVec2i& a, const i32 scaler)
{
    return primeDivVec2i_s(a, scaler);
}

PRIME_INLINE primeVec2i operator * (const primeVec2i& a, const primeVec2i& b)
{
    return primeMulVec2i(a, b);
}

PRIME_INLINE primeVec2i operator * (const primeVec2i& a, const i32 scaler)
{
    return primeMulVec2i_s(a, scaler);
}

PRIME_INLINE primeVec2i& operator += (primeVec2i& a, const primeVec2i& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

PRIME_INLINE primeVec2i& operator -= (primeVec2i& a, const primeVec2i& b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

PRIME_INLINE primeVec2i& operator /= (primeVec2i& a, const primeVec2i& b)
{
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

PRIME_INLINE primeVec2i& operator /= (primeVec2i& a, i32 scaler)
{
    a.x /= scaler;
    a.y /= scaler;
    return a;
}

PRIME_INLINE primeVec2i& operator *= (primeVec2i& a, const primeVec2i& b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

PRIME_INLINE primeVec2i& operator *= (primeVec2i& a, i32 scaler)
{
    a.x *= scaler;
    a.y *= scaler;
    return a;
}

PRIME_INLINE b8 operator == (const primeVec2i& a, const primeVec2i& b)
{
    return primeVec2iEqual(a, b);
}

#endif // __cplusplus