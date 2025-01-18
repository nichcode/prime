#pragma once

#include "pr_maths.h"

struct PrVec2
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

PR_INLINE PrVec2
prVec2Create(f32 x, f32 y)
{
    PrVec2 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

PR_INLINE PrVec2
prVec2Zero()
{
    return prVec2Create(0.0f, 0.0f);
}

PR_INLINE PrVec2
prVec2One()
{
    return prVec2Create(1.0f, 1.0f);
}

PR_INLINE PrVec2
prVec2Add(const PrVec2& vec1, const PrVec2& vec2)
{
    return prVec2Create(vec1.x + vec2.x, vec1.y + vec2.y);
}

PR_INLINE PrVec2
prVec2Sub(const PrVec2& vec1, const PrVec2& vec2)
{
    return prVec2Create(vec1.x - vec2.x, vec1.y - vec2.y);
}

PR_INLINE PrVec2
prVec2Div(const PrVec2& vec1, const PrVec2& vec2)
{
    return prVec2Create(vec1.x / vec2.x, vec1.y / vec2.y);
}

PR_INLINE PrVec2
prVec2Mul(const PrVec2& vec1, const PrVec2& vec2)
{
    return prVec2Create(vec1.x * vec2.x, vec1.y * vec2.y);
}

PR_INLINE PrVec2
prVec2Scale(const PrVec2& vec, f32 scaler)
{
    return prVec2Create(vec.x * scaler, vec.y * scaler);
}

PR_INLINE f32
prVec2LengthSquared(const PrVec2& vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

PR_INLINE f32
prVec2Length(const PrVec2& vec)
{
    return prMathSqrt(vec.x * vec.x + vec.y * vec.y);
}

PR_INLINE void
prVec2Normalize(PrVec2& vec)
{
    const f32 length = prVec2Length(vec);
    vec.x /= length;
    vec.y /= length;
}

PR_INLINE f32
prVec2DistanceSquared(const PrVec2& vec1, const PrVec2& vec2)
{
    PrVec2 vec = prVec2Create(vec1.x - vec2.x, vec1.y - vec2.y);
    return prVec2LengthSquared(vec);
}

PR_INLINE f32
prVec2Distance(const PrVec2& vec1, const PrVec2& vec2)
{
    PrVec2 vec = prVec2Create(vec1.x - vec2.x, vec1.y - vec2.y);
    return prVec2Length(vec);
}

PR_API PrString*
prVec2ToString(const PrVec2& vec);


#ifdef __cplusplus

inline PrVec2 operator + (const PrVec2& vec1, const PrVec2& vec2)
{
    return prVec2Add(vec1, vec2);
}

inline PrVec2 operator - (const PrVec2& vec1, const PrVec2& vec2)
{
    return prVec2Sub(vec1, vec2);
}

inline PrVec2 operator / (const PrVec2& vec1, const PrVec2& vec2)
{
    return prVec2Div(vec1, vec2);
}

inline PrVec2 operator * (const PrVec2& vec1, const PrVec2& vec2)
{
    return prVec2Mul(vec1, vec2);
}

inline PrVec2 operator * (const PrVec2& vec1, f32 scaler)
{
    return prVec2Scale(vec1, scaler);
}

inline PrVec2& operator += (PrVec2& vec1, const PrVec2& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    return vec1;
}

inline PrVec2& operator -= (PrVec2& vec1, const PrVec2& vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    return vec1;
}

inline PrVec2& operator /= (PrVec2& vec1, const PrVec2& vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    return vec1;
}

inline PrVec2& operator *= (PrVec2& vec1, const PrVec2& vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    return vec1;
}

inline PrVec2& operator *= (PrVec2& vec1, f32 scaler)
{
    vec1.x *= scaler;
    vec1.y *= scaler;
    return vec1;
}

#endif // __cplusplus