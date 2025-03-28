
#pragma once

#include "prime/maths.h"
#include "prime/string.h"

struct primeVec3
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
};

PRIME_INLINE primeVec3 primeCreateVec3(f32 x, f32 y, f32 z)
{
    primeVec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

PRIME_INLINE primeVec3 primeAddVec3(const primeVec3 a, const primeVec3 b)
{
    return primeCreateVec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

PRIME_INLINE primeVec3 primeSubVec3(const primeVec3 a, const primeVec3 b)
{
    return primeCreateVec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

PRIME_INLINE primeVec3 primeDivVec3(const primeVec3 a, const primeVec3 b)
{
    return primeCreateVec3(a.x / b.x, a.y / b.y, a.z / b.z);
}

PRIME_INLINE primeVec3 primeDivVec3_s(const primeVec3 a, f32 scaler)
{
    return primeCreateVec3(a.x / scaler, a.y / scaler, a.z / scaler);
}

PRIME_INLINE primeVec3 primeMulVec3(const primeVec3 a, const primeVec3 b)
{
    return primeCreateVec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

PRIME_INLINE primeVec3 primeMulVec3_s(const primeVec3 a, f32 scaler)
{
    return primeCreateVec3(a.x * scaler, a.y * scaler, a.z * scaler);
}

PRIME_INLINE f32 primeVec3Length(const primeVec3 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

PRIME_INLINE f32 primeVec3Length_s(const primeVec3 vec)
{
    return primeSqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

PRIME_INLINE f32 primeVec3Distance(const primeVec3 a, const primeVec3 b)
{
    primeVec3 vec = primeCreateVec3(a.x - b.x, a.y - b.y, a.z - b.z);
    return primeVec3Length(vec);
}

PRIME_INLINE f32 primeVec3Distance_s(const primeVec3 a, const primeVec3 b)
{
    primeVec3 vec = primeCreateVec3(a.x - b.x, a.y - b.y, a.z - b.z);
    return primeVec3Length_s(vec);
}

PRIME_INLINE primeVec3 primeVec3Normalized(const primeVec3 vec)
{
    primeVec3 v = vec;
    const f32 length = primeVec3Length(vec);
    v.x /= length;
    v.y /= length;
    v.z /= length;
    return v;
}

PRIME_INLINE f32 primeVec3Dot(const primeVec3 a, const primeVec3 b)
{
    f32 p = 0;
    p += a.x * b.x;
    p += a.y * b.y;
    p += a.z * b.z;
    return p;
}

PRIME_INLINE primeVec3 primeVec3Cross(const primeVec3 a, const primeVec3 b)
{
    return primeCreateVec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
}

PRIME_INLINE b8 primeVec3Equal(const primeVec3 a, const primeVec3 b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

PRIME_INLINE char* primeVec3ToString(primeVec3 vec)
{
    return primeFormat("vec3(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
}

#ifdef __cplusplus

PRIME_INLINE primeVec3 operator + (const primeVec3& a, const primeVec3& b)
{
    return primeAddVec3(a, b);
}

PRIME_INLINE primeVec3 operator - (const primeVec3& a, const primeVec3& b)
{
    return primeSubVec3(a, b);
}

PRIME_INLINE primeVec3 operator / (const primeVec3& a, const primeVec3& b)
{
    return primeDivVec3(a, b);
}

PRIME_INLINE primeVec3 operator / (const primeVec3& a, const f32 scaler)
{
    return primeDivVec3_s(a, scaler);
}

PRIME_INLINE primeVec3 operator * (const primeVec3& a, const primeVec3& b)
{
    return primeMulVec3(a, b);
}

PRIME_INLINE primeVec3 operator * (const primeVec3& a, const f32 scaler)
{
    return primeMulVec3_s(a, scaler);
}

PRIME_INLINE primeVec3& operator += (primeVec3& a, const primeVec3& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

PRIME_INLINE primeVec3& operator -= (primeVec3& a, const primeVec3& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

PRIME_INLINE primeVec3& operator /= (primeVec3& a, const primeVec3& b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

PRIME_INLINE primeVec3& operator /= (primeVec3& a, f32 scaler)
{
    a.x /= scaler;
    a.y /= scaler;
    a.z /= scaler;
    return a;
}

PRIME_INLINE primeVec3& operator *= (primeVec3& a, const primeVec3& b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.y;
    return a;
}

PRIME_INLINE primeVec3& operator *= (primeVec3& a, f32 scaler)
{
    a.x *= scaler;
    a.y *= scaler;
    a.z *= scaler;
    return a;
}

PRIME_INLINE b8 operator == (const primeVec3& a, const primeVec3& b)
{
    return primeVec3Equal(a, b);
}

#endif // __cplusplus