#pragma once

#include "prime_defines.h"

PRIME_API prime_Texture2D*
prime_Texture2DCreate(prime_Device* device, u32 width, u32 height, prime_Texture2DFormat format, b8 empty);

PRIME_API prime_Texture2D*
prime_Texture2DLoad(prime_Device* device, const char* filepath);

PRIME_API void
prime_Texture2DDestroy(prime_Texture2D* texture2d);

PRIME_API void
prime_Texture2DBind(prime_Texture2D* texture2d, u32 slot = 0);

PRIME_API void
prime_Texture2DUnbind(prime_Texture2D* texture2d);

PRIME_API void
prime_Texture2DSetData(prime_Texture2D* texture2d, const void* data, u32 size);

PRIME_API u32
prime_Texture2DGetWidth(prime_Texture2D* texture2d);

PRIME_API u32
prime_Texture2DGetHeight(prime_Texture2D* texture2d);