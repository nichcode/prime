
#pragma once

#include "prime/maths.h"
#include "prime/string.h"

struct primeVec4
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
    f32 w = 0.0f;
};

PRIME_INLINE primeVec4 primeCreateVec4(f32 x, f32 y, f32 z, f32 w)
{
    primeVec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

PRIME_INLINE primeVec4 primeAddVec4(const primeVec4 a, const primeVec4 b)
{
    return primeCreateVec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

PRIME_INLINE primeVec4 primeSubVec4(const primeVec4 a, const primeVec4 b)
{
    return primeCreateVec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

PRIME_INLINE primeVec4 primeDivVec4(const primeVec4 a, const primeVec4 b)
{
    return primeCreateVec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

PRIME_INLINE primeVec4 primeDivVec4_s(const primeVec4 a, f32 scaler)
{
    return primeCreateVec4(a.x / scaler, a.y / scaler, a.z / scaler, a.w / scaler);
}

PRIME_INLINE primeVec4 primeMulVec4(const primeVec4 a, const primeVec4 b)
{
    return primeCreateVec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

PRIME_INLINE primeVec4 primeMulVec4_s(const primeVec4 a, f32 scaler)
{
    return primeCreateVec4(a.x * scaler, a.y * scaler, a.z * scaler, a.w * scaler);
}

PRIME_INLINE f32 primeVec4Length(const primeVec4 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

PRIME_INLINE f32 primeVec4Length_s(const primeVec4 vec)
{
    return primeSqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

PRIME_INLINE f32 primeVec4Distance(const primeVec4 a, const primeVec4 b)
{
    primeVec4 vec = primeCreateVec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    return primeVec4Length(vec);
}

PRIME_INLINE f32 primeVec4Distance_s(const primeVec4 a, const primeVec4 b)
{
    primeVec4 vec = primeCreateVec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    return primeVec4Length_s(vec);
}

PRIME_INLINE primeVec4 primeVec4Normalized(const primeVec4 vec)
{
    primeVec4 v = vec;
    const f32 length = primeVec4Length(vec);
    v.x /= length;
    v.y /= length;
    v.z /= length;
    v.w /= length;
    return v;
}

PRIME_INLINE b8 primeVec4Equal(const primeVec4 a, const primeVec4 b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

PRIME_INLINE char* primeVec4ToString(primeVec4 vec)
{
    return primeFormat("vec4(%.2f, %.2f, %.2f, %.2f)", vec.x, vec.y, vec.z, vec.w);
}

#ifdef __cplusplus

PRIME_INLINE primeVec4 operator + (const primeVec4& a, const primeVec4& b)
{
    return primeAddVec4(a, b);
}

PRIME_INLINE primeVec4 operator - (const primeVec4& a, const primeVec4& b)
{
    return primeSubVec4(a, b);
}

PRIME_INLINE primeVec4 operator / (const primeVec4& a, const primeVec4& b)
{
    return primeDivVec4(a, b);
}

PRIME_INLINE primeVec4 operator / (const primeVec4& a, const f32 scaler)
{
    return primeDivVec4_s(a, scaler);
}

PRIME_INLINE primeVec4 operator * (const primeVec4& a, const primeVec4& b)
{
    return primeMulVec4(a, b);
}

PRIME_INLINE primeVec4 operator * (const primeVec4& a, const f32 scaler)
{
    return primeMulVec4_s(a, scaler);
}

PRIME_INLINE primeVec4& operator += (primeVec4& a, const primeVec4& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

PRIME_INLINE primeVec4& operator -= (primeVec4& a, const primeVec4& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

PRIME_INLINE primeVec4& operator /= (primeVec4& a, const primeVec4& b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

PRIME_INLINE primeVec4& operator /= (primeVec4& a, f32 scaler)
{
    a.x /= scaler;
    a.y /= scaler;
    a.z /= scaler;
    a.w /= scaler;
    return a;
}

PRIME_INLINE primeVec4& operator *= (primeVec4& a, const primeVec4& b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.y;
    a.w *= b.y;
    return a;
}

PRIME_INLINE primeVec4& operator *= (primeVec4& a, f32 scaler)
{
    a.x *= scaler;
    a.y *= scaler;
    a.z *= scaler;
    a.w *= scaler;
    return a;
}

PRIME_INLINE b8 operator == (const primeVec4& a, const primeVec4& b)
{
    return primeVec4Equal(a, b);
}

#endif // __cplusplus