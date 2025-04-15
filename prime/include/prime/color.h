
#pragma once

#include "defines.h"

struct prColor
{
    f32 r = 1.0f;
    f32 g = 1.0f;
    f32 b = 1.0f;
    f32 a = 1.0f;
};

inline prColor prColorFromU8(u8 r, u8 g, u8 b, u8 a)
{
    prColor color;
    color.r = (f32)r / 255.0f;
    color.g = (f32)g / 255.0f;
    color.b = (f32)b / 255.0f;
    color.a = (f32)a / 255.0f;

    return color;
}

#define PR_RED { 1.0f, 0.0f, 0.0f, 1.0f }
#define PR_GREEN { 0.0f, 1.0f, 0.0f, 1.0f }
#define PR_BLUE { 0.0f, 0.0f, 1.0f, 1.0f }
#define PR_WHITE { 1.0f, 1.0f, 1.0f, 1.0f }
#define PR_BLACK { 0.0f, 0.0f, 0.0f, 1.0f }