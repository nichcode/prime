#pragma once

#include "prime_defines.h"

PRIME_API prime_Renderer2D*
prime_Renderer2DCreate(prime_Device* device, prime_Window* window);

PRIME_API void
prime_Renderer2DDestroy(prime_Renderer2D* renderer2d);

PRIME_API void
prime_Renderer2DSetClearColor(prime_Renderer2D* renderer2d, const prime_Color& color);

PRIME_API void
prime_Renderer2DSetVsync(prime_Renderer2D* renderer2d, b8 vsync);

PRIME_API void
prime_Renderer2DSetViewport(prime_Renderer2D* renderer2d, const prime_Viewport& viewport);

PRIME_API void
prime_Renderer2DClear(prime_Renderer2D* renderer2d);

PRIME_API void
prime_Renderer2DBegin(prime_Renderer2D* renderer2d);

PRIME_API void
prime_Renderer2DEnd(prime_Renderer2D* renderer2d);

PRIME_API void
prime_Renderer2DDrawRect(prime_Renderer2D* renderer2d, prime_Rect2D rect);

PRIME_API void
prime_Renderer2DPresent(prime_Renderer2D* renderer2d);

PRIME_API const prime_Viewport& 
prime_Renderer2DGetViewport(prime_Renderer2D* renderer2d);
