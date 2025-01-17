#pragma once

#include "pr_defines.h"

struct PrColor
{
    f32 r = 0.0f;
    f32 g = 0.0f;
    f32 b = 0.0f;
    f32 a = 0.0f;
};

PR_INLINE PrColor
prColorFromU8(u8 r, u8 g, u8 b, u8 a)
{
    PrColor color;
    color.r = (f32)r / 255.0f;
    color.g = (f32)g / 255.0f;
    color.b = (f32)b / 255.0f;
    color.a = (f32)a / 255.0f;
    return color;
}

PR_INLINE PrColor
prColorFromf32(f32 r, f32 g, f32 b, f32 a)
{
    PrColor color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}