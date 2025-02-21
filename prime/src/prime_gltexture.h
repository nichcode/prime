
#pragma once

#include "prime/prime_texture.h"

void*
primeGLTexture2DCreate(const primeTexture2DDesc* desc);

void*
primeGLTexture2DLoad(const char* filepath, u32* width, u32* height);

void
primeGLTexture2DDestroy(void* handle);

void
primeGLTexture2DBind(void* handle, u32 slot);

void
primeGLTexture2DUnbind(void* handle);

void
primeGLTexture2DSetData(void* handle, const void* data, u32 width, u32 height);

u32
primeGLTexture2DGetHandle(void* handle);