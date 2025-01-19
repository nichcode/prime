#pragma once

#include "prime_defines.h"

struct prime_Color
{
    f32 r = 0.0f;
    f32 g = 0.0f;
    f32 b = 0.0f;
    f32 a = 0.0f;
};

PRIME_INLINE prime_Color
prime_ColorFromU8(u8 r, u8 g, u8 b, u8 a)
{
    prime_Color color;
    color.r = (f32)r / 255.0f;
    color.g = (f32)g / 255.0f;
    color.b = (f32)b / 255.0f;
    color.a = (f32)a / 255.0f;
    return color;
}

PRIME_INLINE prime_Color
prime_ColorFromF32(f32 r, f32 g, f32 b, f32 a)
{
    prime_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

PRIME_INLINE u32
prime_ColorToU32(const prime_Color& color)
{
    u32 r = (u32)(color.r * 255.0f);
    u32 g = (u32)(color.g * 255.0f);
    u32 b = (u32)(color.b * 255.0f);

    u32 out_color = (((r & 0x0FF) << 16) | ((g & 0x0FF) << 8) | (b & 0x0FF));
}

PRIME_INLINE prime_Color
prColorFromU32(u32 rgba)
{
    prime_Color color;
    u32 r = (rgba >> 16) & 0x0FF;
    u32 g = (rgba >> 8) & 0x0FF;
    u32 b = (rgba) & 0x0FF;

    color.r = (f32)r / 255.0f;
    color.r = (f32)g / 255.0f;
    color.r = (f32)b / 255.0f;
    color.a = 1.0f / 255.0f;
}