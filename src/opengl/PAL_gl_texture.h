
#pragma once

#include "PAL/PAL_texture.h"

void* _GLCreateTexture(PAL_TextureDesc desc);
void* _GLLoadTexture(const char* filepath, u32* width, u32* height);
void _GLDestroyTexture(void* handle);

void _GLBindTexture(void* handle, u32 slot);

void _GLBindRenderTarget(void* handle, u32 width, u32 height);
void _GLUnbindRenderTarget(void* handle);