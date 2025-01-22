#pragma once

#include "prime/prime_defines.h"

void*
gl_RenderTarget2DCreate(prime_Device* device, u32 width, u32 height);

void
gl_RenderTarget2DDestroy(void* rendertarget2d);

void
gl_RenderTarget2DBind(void* rendertarget2d, u32 width, u32 height);

void
gl_RenderTarget2DUnbind(void* rendertarget2d);

void
gl_RenderTarget2DResize(prime_Device* device, void* rendertarget2d, u32 width, u32 height);

prime_Texture2D*
gl_RenderTarget2DGetTexture2D(void* rendertarget2d);