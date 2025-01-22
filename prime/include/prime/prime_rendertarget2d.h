#pragma once

#include "prime_defines.h"

PRIME_API prime_RenderTarget2D*
prime_RenderTarget2DCreate(prime_Device* device, u32 width, u32 height);

PRIME_API void
prime_RenderTarget2DDestroy(prime_RenderTarget2D* rendertarget2d);

PRIME_API void
prime_RenderTarget2DBind(prime_RenderTarget2D* rendertarget2d);

PRIME_API void
prime_RenderTarget2DUnbind(prime_RenderTarget2D* rendertarget2d);

PRIME_API void
prime_RenderTarget2DResize(prime_RenderTarget2D* rendertarget2d, u32 width, u32 height);

PRIME_API u32
prime_RenderTarget2DGetWidth(prime_RenderTarget2D* rendertarget2d);

PRIME_API u32
prime_RenderTarget2DGetHeight(prime_RenderTarget2D* rendertarget2d);

PRIME_API prime_Texture2D*
prime_RenderTarget2DGetTexture2D(prime_RenderTarget2D* rendertarget2d);