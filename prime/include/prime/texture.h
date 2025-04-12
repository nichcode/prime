
#pragma once

#include "defines.h"

struct prTexture;

enum prTextureFlags_
{
    prTextureFlags_None,
    prTextureFlags_Target,
    prTextureFlags_Storage
};

enum prTextureFormats_
{
    prTextureFormats_R8,
    prTextureFormats_RGB8,
    prTextureFormats_RGB16,
    prTextureFormats_RGB16F,
    prTextureFormats_RGB32F,
    prTextureFormats_RGBA8,
    prTextureFormats_RGBA16,
    prTextureFormats_RGBA16F,
    prTextureFormats_RGBA32F
};

struct prTextureDesc
{
    u32 flag = 0;
    u32 format = 0;
    u32 width = 1;
    u32 height = 1;
    void* storage_data = nullptr;
};

PR_API prTexture* prCreateTexture(prTextureDesc desc);
PR_API prTexture* prLoadTexture(const char* filepath);
PR_API void prDestroyTexture(prTexture* texture);

PR_API void prBindTexture(prTexture* texture, u32 slot);
PR_API void prBindTarget(prTexture* texture);
PR_API void prUnbindTarget(prTexture* texture);

PR_API u32 prGetTextureWidth(prTexture* texture);
PR_API u32 prGetTextureHeight(prTexture* texture);
PR_API const char* prGetTexturePath(prTexture* texture);