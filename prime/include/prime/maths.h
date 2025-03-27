
#pragma once

#include "defines.h"

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

struct primeVec2
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

PRIME_INLINE primeVec2 primeCreateVec2(f32 x, f32 y)
{
    primeVec2 v;
    v.x = x;
    v.y = y;
    return v;
}

struct primeVec2i
{
    i32 x = 0;
    i32 y = 0;
};

PRIME_INLINE primeVec2i primeCreateVec2i(i32 x, i32 y)
{
    primeVec2i v;
    v.x = x;
    v.y = y;
    return v;
}

struct primeVec2u
{
    u32 x = 0;
    u32 y = 0;
};

PRIME_INLINE primeVec2u primeCreateVec2u(u32 x, u32 y)
{
    primeVec2u v;
    v.x = x;
    v.y = y;
    return v;
}

struct primeVec3
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
};

PRIME_INLINE primeVec3 primeCreateVec3(f32 x, f32 y, f32 z)
{
    primeVec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

struct primeVec3i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
};

PRIME_INLINE primeVec3i primeCreateVec3i(i32 x, i32 y, i32 z)
{
    primeVec3i v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

struct primeVec3u
{
    u32 x = 0;
    u32 y = 0;
    u32 z = 0;
};

PRIME_INLINE primeVec3u primeCreateVec3u(u32 x, u32 y, u32 z)
{
    primeVec3u v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

struct primeVec4
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
    f32 w = 0.0f;
};

PRIME_INLINE primeVec4 primeCreateVec4(f32 x, f32 y, f32 z, f32 w)
{
    primeVec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

struct primeVec4i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
    i32 w = 0;
};

PRIME_INLINE primeVec4i primeCreateVec4i(i32 x, i32 y, i32 z, i32 w)
{
    primeVec4i v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

struct primeVec4u
{
    u32 x = 0;
    u32 y = 0;
    u32 z = 0;
    u32 w = 0;
};

PRIME_INLINE primeVec4u primeCreateVec4u(u32 x, u32 y, u32 z, u32 w)
{
    primeVec4u v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

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