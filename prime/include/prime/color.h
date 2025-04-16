
#pragma once

#include "defines.h"

/// @brief Color
struct prColor
{
    f32 r = 1.0f;
    f32 g = 1.0f;
    f32 b = 1.0f;
    f32 a = 1.0f;
};

/**
 * @brief Create a color from a set of rgba values in (0-255) range
 * @param r The red component of the color
 * @param g The green component of the color
 * @param b The blue component of the color
 * @param a The alpha component of the color
 * @returns a color
 */
inline prColor prColorFromU8(u8 r, u8 g, u8 b, u8 a)
{
    prColor color;
    color.r = (f32)r / 255.0f;
    color.g = (f32)g / 255.0f;
    color.b = (f32)b / 255.0f;
    color.a = (f32)a / 255.0f;

    return color;
}

/// @brief Color red
#define PR_RED { 1.0f, 0.0f, 0.0f, 1.0f }

/// @brief Color green
#define PR_GREEN { 0.0f, 1.0f, 0.0f, 1.0f }

/// @brief Color blue
#define PR_BLUE { 0.0f, 0.0f, 1.0f, 1.0f }

/// @brief Color white
#define PR_WHITE { 1.0f, 1.0f, 1.0f, 1.0f }

/// @brief Color black
#define PR_BLACK { 0.0f, 0.0f, 0.0f, 1.0f }