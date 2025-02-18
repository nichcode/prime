
#include "prime_defines.h"

struct primeVec2
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

struct primeVec3
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
};

struct primeVec4
{
    // TODO: use SIMD
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
    f32 w = 0.0f;
};

struct primeMat4
{
    f32 data[16]{};
};