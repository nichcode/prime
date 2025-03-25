
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
    f32 data[16];
};