
#pragma once

#include "prime/vec2i.h"

struct primeTexture;
struct primeSubTexture;

using primeTextureFlag = u32;
using primeTextureFormat = u32;

enum primeTextureFlags_
{
    primeTextureFlags_None,
    primeTextureFlags_Target,
    primeTextureFlags_Storage
};

enum primeTextureFormats_
{
    primeTextureFormat_R8,
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
    primeVec2i size = primeCreateVec2i(1, 1);
    void* data = nullptr;
};

PRIME_API primeTexture* primeCreateTexture(primeTextureDesc desc);
PRIME_API primeTexture* primeLoadTexture(const char* filepath);
PRIME_API primeSubTexture* primeGetSubTexture(primeTexture* texture, u32 x, u32 y, u32 w, u32 h);

PRIME_API void primeDestroyTexture(primeTexture* texture);
PRIME_API void primeDestroySubTexture(primeSubTexture* sub_texture);

PRIME_API void primeSetTextureData(primeTexture* texture, u32 x, u32 y, u32 width, u32 height, void* data);

PRIME_API primeVec2i primeGetTextureSize(primeTexture* texture);

PRIME_API void primeBindTexture(primeTexture* texture, u32 slot);
PRIME_API void primeUnbindTexture(primeTexture* texture);

PRIME_API void primeBindRenderTarget(primeTexture* texture);
PRIME_API void primeUnbindRenderTarget(primeTexture* texture);