#pragma once

#include "prime_defines.h"
#include "prime_math.h"

PRIME_API prime_Renderer2D*
prime_Renderer2DCreate(prime_Device* device, prime_Window* window);

PRIME_API void
prime_Renderer2DDestroy(prime_Renderer2D* renderer2d);

PRIME_API void
prime_Renderer2DSetClearColor(prime_Renderer2D* renderer2d, const prime_Color& color);

PRIME_API void
prime_Renderer2DSetDrawColor(prime_Renderer2D* renderer2d, const prime_Color& color);

PRIME_API void
prime_Renderer2DSetLinesWidth(prime_Renderer2D* renderer2d, f32 width);

PRIME_API void
prime_Renderer2DSetAntiAliasing(prime_Renderer2D* renderer2d, b8 anti_aliasing);

PRIME_API void
prime_Renderer2DSetVsync(prime_Renderer2D* renderer2d, b8 vsync);

PRIME_API void
prime_Renderer2DSetViewport(prime_Renderer2D* renderer2d, const prime_Viewport& viewport);

PRIME_API void
prime_Renderer2DSetScale(prime_Renderer2D* renderer2d, prime_Vec2 scale);

PRIME_API void
prime_Renderer2DClear(prime_Renderer2D* renderer2d);

PRIME_API void
prime_Renderer2DBegin(prime_Renderer2D* renderer2d);

PRIME_API void
prime_Renderer2DEnd(prime_Renderer2D* renderer2d);

PRIME_API void
prime_Renderer2DDrawRect(prime_Renderer2D* renderer2d, const prime_Rect2D& rect, b8 filled = true);

PRIME_API void
prime_Renderer2DDrawRectEx(prime_Renderer2D* renderer2d, const prime_Rect2D& rect, f32 rotation, prime_Anchor anchor, b8 filled = true);

PRIME_API void
prime_Renderer2DDrawSprite(prime_Renderer2D* renderer2d, const prime_Rect2D& rect, prime_Texture2D* texture2d);

PRIME_API void
prime_Renderer2DDrawSpriteEx(
	prime_Renderer2D* renderer2d,
	const prime_Rect2D& rect,
	prime_Texture2D* texture2d,
	f32 rotation,
	prime_Anchor anchor,
	b8 flip_x,
	b8 flip_y,
	const prime_Color& tint_color = prime_ColorFromF32(1.0f, 1.0f, 1.0f, 1.0f));

PRIME_API void
prime_Renderer2DDrawLine(prime_Renderer2D* renderer2d, const prime_Vec2& point1, const prime_Vec2& point2);

PRIME_API void
prime_Renderer2DPresent(prime_Renderer2D* renderer2d);

PRIME_API const prime_Viewport& 
prime_Renderer2DGetViewport(prime_Renderer2D* renderer2d);

PRIME_API const prime_Color&
prime_Renderer2DGetDrawColor(prime_Renderer2D* renderer2d);

PRIME_API f32
prime_Renderer2DGetLinesWidth(prime_Renderer2D* renderer2d);

PRIME_API b8
prime_Renderer2DGetAntiAliasing(prime_Renderer2D* renderer2d);

PRIME_API b8
prime_Renderer2DGetVsync(prime_Renderer2D* renderer2d);
