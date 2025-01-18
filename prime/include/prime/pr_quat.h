#pragma once

#include "pr_math.h"

struct PrQuat
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
    f32 w = 0.0f;
};

PR_INLINE PrQuat
prQuatCreate(f32 x, f32 y, f32 z, f32 w) 
{
    PrQuat quat;
    quat.x = x;
    quat.y = y;
    quat.z = z;
    quat.w = w;
    return quat;
}

PR_INLINE PrQuat
prQuatNormalize(PrQuat& quat) 
{
    f32 normal = prMathSqrt(quat.x * quat.x + quat.y * quat.y + quat.z * quat.z + quat.w * quat.w);
    return prQuatCreate(quat.x / normal, quat.y / normal, quat.z / normal, quat.w / normal);
}

PR_API PrString*
prQuatToString(const PrQuat& vec);