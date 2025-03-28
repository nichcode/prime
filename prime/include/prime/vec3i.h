
#pragma once

#include "prime/maths.h"
#include "prime/string.h"

struct primeVec3i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
};

PRIME_INLINE primeVec3i primeCreateVec3i(i32 x, i32 y, i32 z)
{
    primeVec3i v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

PRIME_INLINE primeVec3i primeAddVec3i(const primeVec3i a, const primeVec3i b)
{
    return primeCreateVec3i(a.x + b.x, a.y + b.y, a.z + b.z);
}

PRIME_INLINE primeVec3i primeSubVec3i(const primeVec3i a, const primeVec3i b)
{
    return primeCreateVec3i(a.x - b.x, a.y - b.y, a.z - b.z);
}

PRIME_INLINE primeVec3i primeDivVec3i(const primeVec3i a, const primeVec3i b)
{
    return primeCreateVec3i(a.x / b.x, a.y / b.y, a.z / b.z);
}

PRIME_INLINE primeVec3i primeDivVec3_s(const primeVec3i a, i32 scaler)
{
    return primeCreateVec3i(a.x / scaler, a.y / scaler, a.z / scaler);
}

PRIME_INLINE primeVec3i primeMulVec3i(const primeVec3i a, const primeVec3i b)
{
    return primeCreateVec3i(a.x * b.x, a.y * b.y, a.z * b.z);
}

PRIME_INLINE primeVec3i primeMulVec3_s(const primeVec3i a, i32 scaler)
{
    return primeCreateVec3i(a.x * scaler, a.y * scaler, a.z * scaler);
}

PRIME_INLINE b8 primeVec3iEqual(const primeVec3i a, const primeVec3i b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

PRIME_INLINE char* primeVec3iToString(primeVec3i vec)
{
    return primeFormat("vec3i(%i, %i, %i)", vec.x, vec.y, vec.z);
}

#ifdef __cplusplus

PRIME_INLINE primeVec3i operator + (const primeVec3i& a, const primeVec3i& b)
{
    return primeAddVec3i(a, b);
}

PRIME_INLINE primeVec3i operator - (const primeVec3i& a, const primeVec3i& b)
{
    return primeSubVec3i(a, b);
}

PRIME_INLINE primeVec3i operator / (const primeVec3i& a, const primeVec3i& b)
{
    return primeDivVec3i(a, b);
}

PRIME_INLINE primeVec3i operator / (const primeVec3i& a, const f32 scaler)
{
    return primeDivVec3_s(a, scaler);
}

PRIME_INLINE primeVec3i operator * (const primeVec3i& a, const primeVec3i& b)
{
    return primeMulVec3i(a, b);
}

PRIME_INLINE primeVec3i operator * (const primeVec3i& a, const f32 scaler)
{
    return primeMulVec3_s(a, scaler);
}

PRIME_INLINE primeVec3i& operator += (primeVec3i& a, const primeVec3i& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

PRIME_INLINE primeVec3i& operator -= (primeVec3i& a, const primeVec3i& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

PRIME_INLINE primeVec3i& operator /= (primeVec3i& a, const primeVec3i& b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

PRIME_INLINE primeVec3i& operator /= (primeVec3i& a, f32 scaler)
{
    a.x /= scaler;
    a.y /= scaler;
    a.z /= scaler;
    return a;
}

PRIME_INLINE primeVec3i& operator *= (primeVec3i& a, const primeVec3i& b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.y;
    return a;
}

PRIME_INLINE primeVec3i& operator *= (primeVec3i& a, f32 scaler)
{
    a.x *= scaler;
    a.y *= scaler;
    a.z *= scaler;
    return a;
}

PRIME_INLINE b8 operator == (const primeVec3i& a, const primeVec3i& b)
{
    return primeVec3iEqual(a, b);
}

#endif // __cplusplus