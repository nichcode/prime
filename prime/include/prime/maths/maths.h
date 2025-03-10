
#pragma once

#include "prime/defines.h"

#define PRIME_PI 3.14159265358979323846f

namespace prime::maths {

    f32 sqrt(f32 num);
    f32 tan(f32 num);
    f32 cos(f32 num);
    f32 sin(f32 num);

    PRIME_INLINE f32 toRadians(f32 radians)
    {
        return radians * 180.0f / PRIME_PI;
    }

    PRIME_INLINE f32 toDegrees(f32 degrees)
    {
        return degrees * PRIME_PI / 180.0f;
    }

} // namespace prime::maths 