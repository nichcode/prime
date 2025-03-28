
#pragma once

#include "defines.h"

PRIME_API f32 primeSqrt(f32 number);
PRIME_API f32 primeTan(f32 number);

PRIME_API f32 primeCos(f32 number);
PRIME_API f32 primeSin(f32 number);

PRIME_INLINE i32 primeMax(i32 a, i32 b)
{
    if(a > b) {
        return a;
    }
    return b;
}

PRIME_INLINE i32 primeMin(i32 a, i32 b)
{
    if(a < b) {
        return a;
    }
    return b;
}

PRIME_INLINE f32 primeToRadians(f32 degrees)
{
    return (PRIME_PI * degrees) / 180.0f;
}

PRIME_INLINE f32 primeToDegrees(f32 radians)
{
    return (radians * 180.0f) / PRIME_PI;
}