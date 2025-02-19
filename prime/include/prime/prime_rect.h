
#pragma once

#include "prime_defines.h"
#include "prime_math.h"

struct primeRect
{
	f32 x = 0.0f;
	f32 y = 0.0f;
	f32 width = 50.0f;
	f32 height = 50.0f;
};

PINLINE primeRect
primeRectCreate(f32 x, f32 y, f32 width, f32 height) 
{
	primeRect rect;
	rect.x = x;
	rect.y = y;
	rect.width = width;
	rect.height = height;
	return rect;
}

PINLINE primeVec2
primeRectGetCenter(const primeRect* rect) 
{
	return primeVec2Create(
		(rect->x + rect->width) / 2.0f,
		(rect->y + rect->height) / 2.0f
	);
}

PINLINE f32
primeRectGetCenterX(const primeRect* rect) 
{
	return (rect->x + rect->width) / 2.0f;
}

PINLINE f32
primeRectGetCenterY(const primeRect* rect) 
{
	return (rect->y + rect->height) / 2.0f;
}

PINLINE primeVec2
primeRectGetTopLeft(const primeRect* rect) 
{
	return primeVec2Create(rect->x, rect->y);
}