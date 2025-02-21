
#pragma once

#include "prime_defines.h"

enum primeTextureFormat
{
	primeTextureFormatR8,
	primeTextureFormatRGB8,
	primeTextureFormatRGBA8,
	primeTextureFormatRGBA32F
};

struct primeTexture2DDesc
{
    u32 width = 1;
    u32 height = 1;
    primeTextureFormat format = primeTextureFormatRGBA8;
    b8 renderTarget = false;
};

PAPI primeTexture2D*
primeTexture2DCreate(primeDevice* device, const primeTexture2DDesc* desc);

PAPI primeTexture2D*
primeTexture2DLoad(primeDevice* device, const char* filepath);

PAPI void
primeTexture2DDestroy(primeTexture2D* texture);

PAPI void
primeTexture2DBind(primeTexture2D* texture, u32 slot = 0);

PAPI void
primeTexture2DUnbind(primeTexture2D* texture);

PAPI void
primeTexture2DSetData(primeTexture2D* texture, const void* data, u32 size);

PAPI u32
primeTexture2DGetWidth(primeTexture2D* texture);

PAPI u32
primeTexture2DGetHeight(primeTexture2D* texture);

PAPI void*
primeTexture2DGetHandle(primeTexture2D* texture);

PAPI b8
primeTexture2DEqual(const primeTexture2D& tex1, const primeTexture2D& tex2);

inline b8 
operator == (const primeTexture2D& tex1, const primeTexture2D& tex2)
{
    return primeTexture2DEqual(tex1, tex2);
}