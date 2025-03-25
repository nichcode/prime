
#pragma once

#include "defines.h"

struct primeVec2
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

struct primeVec2i
{
    i32 x = 0;
    i32 y = 0;
};

struct primeVec2u
{
    u32 x = 0;
    u32 y = 0;
};

struct primeVec3
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
};

struct primeVec3i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
};

struct primeVec3u
{
    u32 x = 0;
    u32 y = 0;
    u32 z = 0;
};

struct primeVec4
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
    f32 w = 0.0f;
};

struct primeVec4i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
    i32 w = 0;
};

struct primeVec4u
{
    u32 x = 0;
    u32 y = 0;
    u32 z = 0;
    u32 w = 0;
};

struct primeMat2
{
    f32 data[8];
};

struct primeMat3
{
    f32 data[12];
};

struct primeMat4
{
    f32 data[16]{};
};

PRIME_INLINE primeMat4 primeIdentity()
{
    primeMat4 mat;
    mat.data[0] = 1.0f;
    mat.data[5] = 1.0f;
    mat.data[10] = 1.0f;
    mat.data[15] = 1.0f;
    return mat;
}

PRIME_INLINE primeMat4 primeOrtho(f32 left, f32 right, f32 bottom, f32 top, f32 near_clip, f32 far_clip)
{
    primeMat4 mat = primeIdentity();

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