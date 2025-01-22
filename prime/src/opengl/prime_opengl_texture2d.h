#pragma once

#include "prime/prime_defines.h"

void*
gl_Texture2DCreate(u32 width, u32 height, prime_Texture2DFormat format,b8 empty);

void*
gl_Texture2DLoad(const char* filepath, u32* width, u32* height);

void
gl_Texture2DDestroy(void* texture2d);

void
gl_Texture2DBind(void* texture2d, u32 slot);

void
gl_Texture2DUnbind(void* texture2d);

void
gl_Texture2DSetData(void* texture2d, const void* data, u32 widht, u32 height);