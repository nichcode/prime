
#pragma once

#include "prime/maths.h"

struct primeTexture;

using primeTextureFlag = u32;
using primeTextureFormat = u32;

enum primeTextureFlags_
{
    primeTextureFlags_None = 0,
    primeTextureFlags_Target = PRIME_BIT(0),
    primeTextureFlags_Storage = PRIME_BIT(1)
};

enum primeTextureFormats_
{
    primeTextureFormat_Red,
    primeTextureFormat_RGB8,
    primeTextureFormat_RGB16,
    primeTextureFormat_RGB16F,
    primeTextureFormat_RGB32F,
    primeTextureFormat_RGBA8,
    primeTextureFormat_RGBA16,
    primeTextureFormat_RGBA16F,
    primeTextureFormat_RGBA32F
};

struct primeTextureDesc
{
    primeTextureFlag flag = primeTextureFlags_None;
    primeTextureFormat format = primeTextureFormat_RGBA8;
    primeVec2u size = primeCreateVec2u(1, 1);
};

PRIME_API primeTexture* primeCreateTexture(primeTextureDesc desc);
PRIME_API primeTexture* primeLoadTexture(const char* filepath);
PRIME_API void primeDestroyTexture(primeTexture* texture);

PRIME_API primeVec2u primeGetTextureSize(primeTexture* texture);

PRIME_API void primeBindTexture(primeTexture* texture, u32 slot);
PRIME_API void primeUnbindTexture(primeTexture* texture);

PRIME_API void primeBindRenderTarget(primeTexture* texture);
PRIME_API void primeUnbindRenderTarget(primeTexture* texture);