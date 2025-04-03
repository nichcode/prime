
#pragma once

#include "prime/prime.h"

#ifdef __cplusplus

PRIME_INLINE prime_vec2 operator + (const prime_vec2& a, const prime_vec2& b)
{
    return prime_add_vec2(a, b);
}

PRIME_INLINE prime_vec2 operator - (const prime_vec2& a, const prime_vec2& b)
{
    return prime_sub_vec2(a, b);
}

PRIME_INLINE prime_vec2 operator / (const prime_vec2& a, const prime_vec2& b)
{
    return prime_div_vec2(a, b);
}

PRIME_INLINE prime_vec2 operator / (const prime_vec2& a, const f32 scaler)
{
    return prime_div_vec2_s(a, scaler);
}

PRIME_INLINE prime_vec2 operator * (const prime_vec2& a, const prime_vec2& b)
{
    return prime_mul_vec2(a, b);
}

PRIME_INLINE prime_vec2 operator * (const prime_vec2& a, const f32 scaler)
{
    return prime_mul_vec2_s(a, scaler);
}

PRIME_INLINE prime_vec2& operator += (prime_vec2& a, const prime_vec2& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

PRIME_INLINE prime_vec2& operator -= (prime_vec2& a, const prime_vec2& b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

PRIME_INLINE prime_vec2& operator /= (prime_vec2& a, const prime_vec2& b)
{
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

PRIME_INLINE prime_vec2& operator /= (prime_vec2& a, f32 scaler)
{
    a.x /= scaler;
    a.y /= scaler;
    return a;
}

PRIME_INLINE prime_vec2& operator *= (prime_vec2& a, const prime_vec2& b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

PRIME_INLINE prime_vec2& operator *= (prime_vec2& a, f32 scaler)
{
    a.x *= scaler;
    a.y *= scaler;
    return a;
}

PRIME_INLINE b8 operator == (const prime_vec2& a, const prime_vec2& b)
{
    return prime_vec2_equal(a, b);
}

PRIME_INLINE prime_vec3 operator + (const prime_vec3& a, const prime_vec3& b)
{
    return prime_add_vec3(a, b);
}

PRIME_INLINE prime_vec3 operator - (const prime_vec3& a, const prime_vec3& b)
{
    return prime_sub_vec3(a, b);
}

PRIME_INLINE prime_vec3 operator / (const prime_vec3& a, const prime_vec3& b)
{
    return prime_div_vec3(a, b);
}

PRIME_INLINE prime_vec3 operator / (const prime_vec3& a, const f32 scaler)
{
    return prime_div_vec3_s(a, scaler);
}

PRIME_INLINE prime_vec3 operator * (const prime_vec3& a, const prime_vec3& b)
{
    return prime_mul_vec3(a, b);
}

PRIME_INLINE prime_vec3 operator * (const prime_vec3& a, const f32 scaler)
{
    return prime_mul_vec3_s(a, scaler);
}

PRIME_INLINE prime_vec3& operator += (prime_vec3& a, const prime_vec3& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

PRIME_INLINE prime_vec3& operator -= (prime_vec3& a, const prime_vec3& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

PRIME_INLINE prime_vec3& operator /= (prime_vec3& a, const prime_vec3& b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

PRIME_INLINE prime_vec3& operator /= (prime_vec3& a, f32 scaler)
{
    a.x /= scaler;
    a.y /= scaler;
    a.z /= scaler;
    return a;
}

PRIME_INLINE prime_vec3& operator *= (prime_vec3& a, const prime_vec3& b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.y;
    return a;
}

PRIME_INLINE prime_vec3& operator *= (prime_vec3& a, f32 scaler)
{
    a.x *= scaler;
    a.y *= scaler;
    a.z *= scaler;
    return a;
}

PRIME_INLINE b8 operator == (const prime_vec3& a, const prime_vec3& b)
{
    return prime_vec3_equal(a, b);
}

PRIME_INLINE prime_vec4 operator + (const prime_vec4& a, const prime_vec4& b)
{
    return prime_add_vec4(a, b);
}

PRIME_INLINE prime_vec4 operator - (const prime_vec4& a, const prime_vec4& b)
{
    return prime_sub_vec4(a, b);
}

PRIME_INLINE prime_vec4 operator / (const prime_vec4& a, const prime_vec4& b)
{
    return prime_div_vec4(a, b);
}

PRIME_INLINE prime_vec4 operator / (const prime_vec4& a, const f32 scaler)
{
    return prime_div_vec4_s(a, scaler);
}

PRIME_INLINE prime_vec4 operator * (const prime_vec4& a, const prime_vec4& b)
{
    return prime_mul_vec4(a, b);
}

PRIME_INLINE prime_vec4 operator * (const prime_vec4& a, const f32 scaler)
{
    return prime_mul_vec4_s(a, scaler);
}

PRIME_INLINE prime_vec4& operator += (prime_vec4& a, const prime_vec4& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

PRIME_INLINE prime_vec4& operator -= (prime_vec4& a, const prime_vec4& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

PRIME_INLINE prime_vec4& operator /= (prime_vec4& a, const prime_vec4& b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

PRIME_INLINE prime_vec4& operator /= (prime_vec4& a, f32 scaler)
{
    a.x /= scaler;
    a.y /= scaler;
    a.z /= scaler;
    a.w /= scaler;
    return a;
}

PRIME_INLINE prime_vec4& operator *= (prime_vec4& a, const prime_vec4& b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.y;
    a.w *= b.y;
    return a;
}

PRIME_INLINE prime_vec4& operator *= (prime_vec4& a, f32 scaler)
{
    a.x *= scaler;
    a.y *= scaler;
    a.z *= scaler;
    a.w *= scaler;
    return a;
}

PRIME_INLINE b8 operator == (const prime_vec4& a, const prime_vec4& b)
{
    return prime_vec4_equal(a, b);
}

PRIME_INLINE prime_mat4 operator * (const prime_mat4& a, const prime_mat4& b)
{
    return prime_mat4_mul(a, b);
}

PRIME_INLINE prime_vec4 operator * (const prime_mat4& mat, const prime_vec4& vec)
{
    return prime_mat4_mul_vec4(mat, vec);
}

PRIME_INLINE prime_vec4 operator * (const prime_vec4& vec, const prime_mat4& mat)
{
    return prime_vec4_mul_mat4(vec, mat);
}

#endif // __cplusplus