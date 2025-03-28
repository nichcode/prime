
#pragma once

#include "prime/maths.h"
#include "prime/string.h"

struct primeVec4i
{
    i32 x = 0.0f;
    i32 y = 0.0f;
    i32 z = 0.0f;
    i32 w = 0.0f;
};

PRIME_INLINE primeVec4i primeCreateVec4i(i32 x, i32 y, i32 z, i32 w)
{
    primeVec4i v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

PRIME_INLINE primeVec4i primeAddVec4i(const primeVec4i a, const primeVec4i b)
{
    return primeCreateVec4i(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

PRIME_INLINE primeVec4i primeSubVec4i(const primeVec4i a, const primeVec4i b)
{
    return primeCreateVec4i(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

PRIME_INLINE primeVec4i primeDivVec4i(const primeVec4i a, const primeVec4i b)
{
    return primeCreateVec4i(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

PRIME_INLINE primeVec4i primeDivVec4_s(const primeVec4i a, i32 scaler)
{
    return primeCreateVec4i(a.x / scaler, a.y / scaler, a.z / scaler, a.w / scaler);
}

PRIME_INLINE primeVec4i primeMulVec4i(const primeVec4i a, const primeVec4i b)
{
    return primeCreateVec4i(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

PRIME_INLINE primeVec4i primeMulVec4_s(const primeVec4i a, i32 scaler)
{
    return primeCreateVec4i(a.x * scaler, a.y * scaler, a.z * scaler, a.w * scaler);
}

PRIME_INLINE b8 primeVec4iEqual(const primeVec4i a, const primeVec4i b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

PRIME_INLINE char* primeVec4iToString(primeVec4i vec)
{
    return primeFormat("vec4i(%i, %i, %i, %i)", vec.x, vec.y, vec.z, vec.w);
}

#ifdef __cplusplus

PRIME_INLINE primeVec4i operator + (const primeVec4i& a, const primeVec4i& b)
{
    return primeAddVec4i(a, b);
}

PRIME_INLINE primeVec4i operator - (const primeVec4i& a, const primeVec4i& b)
{
    return primeSubVec4i(a, b);
}

PRIME_INLINE primeVec4i operator / (const primeVec4i& a, const primeVec4i& b)
{
    return primeDivVec4i(a, b);
}

PRIME_INLINE primeVec4i operator / (const primeVec4i& a, const i32 scaler)
{
    return primeDivVec4_s(a, scaler);
}

PRIME_INLINE primeVec4i operator * (const primeVec4i& a, const primeVec4i& b)
{
    return primeMulVec4i(a, b);
}

PRIME_INLINE primeVec4i operator * (const primeVec4i& a, const i32 scaler)
{
    return primeMulVec4_s(a, scaler);
}

PRIME_INLINE primeVec4i& operator += (primeVec4i& a, const primeVec4i& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

PRIME_INLINE primeVec4i& operator -= (primeVec4i& a, const primeVec4i& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

PRIME_INLINE primeVec4i& operator /= (primeVec4i& a, const primeVec4i& b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

PRIME_INLINE primeVec4i& operator /= (primeVec4i& a, i32 scaler)
{
    a.x /= scaler;
    a.y /= scaler;
    a.z /= scaler;
    a.w /= scaler;
    return a;
}

PRIME_INLINE primeVec4i& operator *= (primeVec4i& a, const primeVec4i& b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.y;
    a.w *= b.y;
    return a;
}

PRIME_INLINE primeVec4i& operator *= (primeVec4i& a, i32 scaler)
{
    a.x *= scaler;
    a.y *= scaler;
    a.z *= scaler;
    a.w *= scaler;
    return a;
}

PRIME_INLINE b8 operator == (const primeVec4i& a, const primeVec4i& b)
{
    return primeVec4iEqual(a, b);
}

#endif // __cplusplus