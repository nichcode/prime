
#pragma once

#include "prime/texture.h"

void* _glCreateTexture(primeTextureDesc desc);
void* _glLoadTexture(const char* filepath, u32* width, u32* height);
void _glDestroyTexture(void* handle);

void _glSetTextureData(void* handle, u32 x, u32 y, u32 width, u32 height, void* data);

void _glBindTexture(void* handle, u32 slot);
void _glUnbindTexture(void* handle);

void _glBindRenderTarget(void* handle, u32 width, u32 height);
void _glUnbindRenderTarget(void* handle);