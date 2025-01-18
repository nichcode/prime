#pragma once

#include "pr_vec3.h"

struct PrVec4
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
    f32 w = 0.0f;
};

PR_INLINE PrVec4
prVec4CreateFromVec2(const PrVec2& vec2)
{
    PrVec4 vec;
    vec.x = vec2.x;
    vec.y = vec2.y;
    vec.z = 0.0f;
    vec.x = 0.0f;
    return vec;
}

PR_INLINE PrVec4
prVec4CreateFromVec3(const PrVec3& vec3)
{
    PrVec4 vec;
    vec.x = vec3.x;
    vec.y = vec3.y;
    vec.z = vec3.z;
    vec.x = 0.0f;
    return vec;
}

PR_INLINE PrVec4
prVec4Create(f32 x, f32 y, f32 z, f32 w)
{
    PrVec4 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;
    return vec;
}

PR_INLINE PrVec4
prVec4Zero()
{
    return prVec4Create(0.0f, 0.0f, 0.0f, 0.0f);
}

PR_INLINE PrVec4
prVec4One()
{
    return prVec4Create(1.0f, 1.0f, 1.0f, 1.0f);
}

PR_INLINE PrVec4
prVec4Up()
{
    return prVec4Create(0.0f, 1.0f, 0.0f, 0.0f);
}

PR_INLINE PrVec4
prVec4Down()
{
    return prVec4Create(0.0f, -1.0f, 0.0f, 0.0f);
}

PR_INLINE PrVec4
prVec4Right()
{
    return prVec4Create(1.0f, 0.0f, 0.0f, 0.0f);
}

PR_INLINE PrVec4
prVec4Left()
{
    return prVec4Create(-1.0f, 0.0f, 0.0f, 0.0f);
}

PR_INLINE PrVec4
prVec4Forward()
{
    return prVec4Create(0.0f, 0.0f, -1.0f, 0.0f);
}

PR_INLINE PrVec4
prVec4Back()
{
    return prVec4Create(0.0f, 0.0f, 1.0f, 0.0f);
}

PR_INLINE PrVec4
prVec4Add(const PrVec4& vec1, const PrVec4& vec2)
{
    return prVec4Create(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
}

PR_INLINE PrVec4
prVec4Sub(const PrVec4& vec1, const PrVec4& vec2)
{
    return prVec4Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
}

PR_INLINE PrVec4
prVec4Div(const PrVec4& vec1, const PrVec4& vec2)
{
    return prVec4Create(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
}

PR_INLINE PrVec4
prVec4Mul(const PrVec4& vec1, const PrVec4& vec2)
{
    return prVec4Create(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
}

PR_INLINE PrVec4
prVec4Scale(const PrVec4& vec, f32 scaler)
{
    return prVec4Create(vec.x * scaler, vec.y * scaler, vec.z * scaler, vec.w * scaler);
}

PR_INLINE f32
prVec4LengthSquared(const PrVec4& vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

PR_INLINE f32
prVec4Length(const PrVec4& vec)
{
    return prMathSqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

PR_INLINE void
prVec4Normalize(PrVec4& vec)
{
    const f32 length = prVec4Length(vec);
    vec.x /= length;
    vec.y /= length;
    vec.z /= length;
    vec.w /= length;
}

PR_INLINE PrVec4
prVec4Normalized(PrVec4& vec)
{
    prVec4Normalize(vec);
    return vec;
}

PR_INLINE f32
prVec4DistanceSquared(const PrVec4& vec1, const PrVec4& vec2)
{
    PrVec4 vec = prVec4Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
    return prVec4LengthSquared(vec);
}

PR_INLINE f32
prVec4Distance(const PrVec4& vec1, const PrVec4& vec2)
{
    PrVec4 vec = prVec4Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
    return prVec4Length(vec);
}

PR_INLINE b8
prVec4Equal(const PrVec4& vec1, const PrVec4& vec2)
{
    return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z && vec1.w == vec2.w;
}

PR_INLINE b8
prVec4NotEqual(const PrVec4& vec1, const PrVec4& vec2)
{
    return vec1.x != vec2.x && vec1.y != vec2.y && vec1.z != vec2.z && vec1.w != vec2.w;
}

PR_API PrString*
prVec4ToString(const PrVec4& vec);


#ifdef __cplusplus

inline PrVec4 operator + (const PrVec4& vec1, const PrVec4& vec2)
{
    return prVec4Add(vec1, vec2);
}

inline PrVec4 operator - (const PrVec4& vec1, const PrVec4& vec2)
{
    return prVec4Sub(vec1, vec2);
}

inline PrVec4 operator / (const PrVec4& vec1, const PrVec4& vec2)
{
    return prVec4Div(vec1, vec2);
}

inline PrVec4 operator * (const PrVec4& vec1, const PrVec4& vec2)
{
    return prVec4Mul(vec1, vec2);
}

inline PrVec4 operator * (const PrVec4& vec1, f32 scaler)
{
    return prVec4Scale(vec1, scaler);
}

inline PrVec4& operator += (PrVec4& vec1, const PrVec4& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    vec1.z += vec2.z;
    vec1.w += vec2.w;
    return vec1;
}

inline PrVec4& operator -= (PrVec4& vec1, const PrVec4& vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    vec1.z -= vec2.z;
    vec1.w -= vec2.w;
    return vec1;
}

inline PrVec4& operator /= (PrVec4& vec1, const PrVec4& vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    vec1.z /= vec2.z;
    vec1.w /= vec2.w;
    return vec1;
}

inline PrVec4& operator *= (PrVec4& vec1, const PrVec4& vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    vec1.z *= vec2.z;
    vec1.w *= vec2.w;
    return vec1;
}

inline PrVec4& operator *= (PrVec4& vec1, f32 scaler)
{
    vec1.x *= scaler;
    vec1.y *= scaler;
    vec1.z *= scaler;
    vec1.w *= scaler;
    return vec1;
}

inline b8 operator == (const PrVec4& vec1, const PrVec4& vec2)
{
    return prVec4Equal(vec1, vec2);
}

inline b8 operator != (const PrVec4& vec1, const PrVec4& vec2)
{
    return prVec4NotEqual(vec1, vec2);
}

#endif // __cplusplus