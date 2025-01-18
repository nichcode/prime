#pragma once

#include "pr_vec2.h"

struct PrVec3
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
};

PR_INLINE PrVec3
prVec3Create(f32 x, f32 y, f32 z)
{
    PrVec3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

PR_INLINE PrVec3
prVec3CreateFromVec2(const PrVec2& vec2)
{
    PrVec3 vec;
    vec.x = vec2.x;
    vec.y = vec2.y;
    vec.z = 0.0f;
    return vec;
}

PR_INLINE PrVec3
prVec3Zero()
{
    return prVec3Create(0.0f, 0.0f, 0.0f);
}

PR_INLINE PrVec3
prVec3One()
{
    return prVec3Create(1.0f, 1.0f, 1.0f);
}

PR_INLINE PrVec3
prVec3Add(const PrVec3& vec1, const PrVec3& vec2)
{
    return prVec3Create(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

PR_INLINE PrVec3
prVec3Sub(const PrVec3& vec1, const PrVec3& vec2)
{
    return prVec3Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

PR_INLINE PrVec3
prVec3Div(const PrVec3& vec1, const PrVec3& vec2)
{
    return prVec3Create(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
}

PR_INLINE PrVec3
prVec3Mul(const PrVec3& vec1, const PrVec3& vec2)
{
    return prVec3Create(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}

PR_INLINE PrVec3
prVec3Scale(const PrVec3& vec, f32 scaler)
{
    return prVec3Create(vec.x * scaler, vec.y * scaler, vec.z * scaler);
}

PR_INLINE f32
prVec3LengthSquared(const PrVec3& vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

PR_INLINE f32
prVec3Length(const PrVec3& vec)
{
    return prMathSqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

PR_INLINE void
prVec3Normalize(PrVec3& vec)
{
    const f32 length = prVec3Length(vec);
    vec.x /= length;
    vec.y /= length;
    vec.z /= length;
}

PR_INLINE f32
prVec3DistanceSquared(const PrVec3& vec1, const PrVec3& vec2)
{
    PrVec3 vec = prVec3Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
    return prVec3LengthSquared(vec);
}

PR_INLINE f32
prVec3Distance(const PrVec3& vec1, const PrVec3& vec2)
{
    PrVec3 vec = prVec3Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
    return prVec3Length(vec);
}

PR_API PrString*
prVec3ToString(const PrVec3& vec);

#ifdef __cplusplus


inline PrVec3 operator + (const PrVec3& vec1, const PrVec3& vec2)
{
    return prVec3Add(vec1, vec2);
}

inline PrVec3 operator - (const PrVec3& vec1, const PrVec3& vec2)
{
    return prVec3Sub(vec1, vec2);
}

inline PrVec3 operator / (const PrVec3& vec1, const PrVec3& vec2)
{
    return prVec3Div(vec1, vec2);
}

inline PrVec3 operator * (const PrVec3& vec1, const PrVec3& vec2)
{
    return prVec3Mul(vec1, vec2);
}

inline PrVec3 operator * (const PrVec3& vec1, f32 scaler)
{
    return prVec3Scale(vec1, scaler);
}

inline PrVec3& operator += (PrVec3& vec1, const PrVec3& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    vec1.z += vec2.z;
    return vec1;
}

inline PrVec3& operator -= (PrVec3& vec1, const PrVec3& vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    vec1.z -= vec2.z;
    return vec1;
}

inline PrVec3& operator /= (PrVec3& vec1, const PrVec3& vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    vec1.z /= vec2.z;
    return vec1;
}

inline PrVec3& operator *= (PrVec3& vec1, const PrVec3& vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    vec1.z *= vec2.z;
    return vec1;
}

inline PrVec3& operator *= (PrVec3& vec1, f32 scaler)
{
    vec1.x *= scaler;
    vec1.y *= scaler;
    vec1.z *= scaler;
    return vec1;
}

#endif // __cplusplus