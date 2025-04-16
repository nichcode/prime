
#pragma once

#include "defines.h"

/// @brief Rect
struct prRect
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 w = 0.0f;
    f32 h = 0.0f;
};

/**
 * @brief Check AABB collision between two rects
 * @param a The first rect
 * @param b The second rect
 * @returns If successful, true otherwise false.
 */
PR_API b8 prRectCollide(const prRect a, const prRect b);