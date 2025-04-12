
#pragma once

#include "prime/texture.h"

void* _GLCreateTexture(prTextureDesc desc);
void* _GLLoadTexture(const char* filepath, u32* width, u32* height);
void _GLDestroyTexture(void* handle);

void _GLBindTexture(void* handle, u32 slot);

void _GLBindRenderTarget(void* handle, u32 width, u32 height);
void _GLUnbindRenderTarget(void* handle);