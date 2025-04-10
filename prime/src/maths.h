
#pragma once

#include "prime/defines.h"
#include "math.h"

struct prVec2
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

struct prVec2i
{
    i32 x = 0;
    i32 y = 0;
};

struct prVec2u
{
    u32 x = 0;
    u32 y = 0;
};

struct prVec3
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
};

struct prVec3i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
};

struct prVec3u
{
    u32 x = 0;
    u32 y = 0;
    u32 z = 0;
};

struct prVec4
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
    f32 w = 0.0f;
};

struct prVec4i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
    i32 w = 0;
};

struct prVec4u
{
    u32 x = 0;
    u32 y = 0;
    u32 z = 0;
    u32 w = 0;
};

struct prMat4
{
    f32 data[16]{};
};

prMat4 prIdentity()
{
    prMat4 mat;
    mat.data[0] = 1.0f;
    mat.data[5] = 1.0f;
    mat.data[10] = 1.0f;
    mat.data[15] = 1.0f;
    return mat;
}

prMat4 prOrtho(f32 left, f32 right, f32 bottom, f32 top, f32 near_clip, f32 far_clip)
{
    prMat4 mat = prIdentity();

    f32 lr = 1.0f / (left - right);
    f32 bt = 1.0f / (bottom - top);
    f32 nf = 1.0f / (near_clip - far_clip);

    mat.data[0] = -2.0f * lr;
    mat.data[5] = -2.0f * bt;
    mat.data[10] = 2.0f * nf;

    mat.data[12] = (left + right) * lr;
    mat.data[13] = (top + bottom) * bt;
    mat.data[14] = (far_clip + near_clip) * nf;

    return mat;
}

prMat4 prPerspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip)
{
    f32 half_tan_fov = tanf(fov_radians * 0.5f);
    prMat4 mat;
    mat.data[0] = 1.0f / (aspect_ratio * half_tan_fov);
    mat.data[5] = 1.0f / half_tan_fov;
    mat.data[10] = -((far_clip + near_clip) / (far_clip - near_clip));
    mat.data[11] = -1.0f;
    mat.data[14] =
        -((2.0f * far_clip * near_clip) / (far_clip - near_clip));

    return mat;
}

prMat4 prTranslate(const prVec3 translation)
{
    prMat4 matrix = prIdentity();
    matrix.data[12] = translation.x;
    matrix.data[13] = translation.y;
    matrix.data[14] = translation.z;
    return matrix;
}

prMat4 prScale(const prVec3 scale)
{
    prMat4 matrix = prIdentity();
    matrix.data[0] = scale.x;
    matrix.data[5] = scale.y;
    matrix.data[10] = scale.z;
    return matrix;
}