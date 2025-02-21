#pragma once

#include "prime_context.h"
#include "prime_math.h"
#include "prime/prime_texture.h"

enum primeAnchor
{
    primeAnchorTopLeft,
    primeAnchorCenter
};

PAPI primeRenderer2D*
primeRenderer2DCreate(primeDevice* device, primeWindow* window);

PAPI void
primeRenderer2DDestroy(primeRenderer2D* renderer);

PAPI void
primeRenderer2DSetClearColor(primeRenderer2D* renderer, primeColor* color);

PAPI void
primeRenderer2DSetLinesWidth(primeRenderer2D* renderer, f32 width);

PAPI void
primeRenderer2DSetAntiAliasing(primeRenderer2D* renderer, b8 anti_aliasing);

PAPI void
primeRenderer2DSetVsync(primeRenderer2D* renderer, b8 vsync);

PAPI void
primeRenderer2DSetView(primeRenderer2D* renderer, primeRect* viewport);

PAPI void
primeRenderer2DSetScale(primeRenderer2D* renderer, primeVec2 scale);

PAPI void
primeRenderer2DClear(primeRenderer2D* renderer);

PAPI void
primeRenderer2DBegin(primeRenderer2D* renderer);

PAPI void
primeRenderer2DEnd(primeRenderer2D* renderer);

PAPI void
primeRenderer2DDrawRect(primeRenderer2D* renderer, const primeRect* rect, primeColor* color);

PAPI void
primeRenderer2DDrawRectEx(primeRenderer2D* renderer, const primeRect* rect, primeColor* color, f32 rotation, primeAnchor anchor);

PAPI void
primeRenderer2DDrawSprite(primeRenderer2D* renderer, const primeRect* rect, primeTexture2D* texture);

PAPI void
primeRenderer2DPresent(primeRenderer2D* renderer);

PAPI const primeRect*
primeRenderer2DGetView(primeRenderer2D* renderer);

PAPI f32
primeRenderer2DGetLinesWidth(primeRenderer2D* renderer);

PAPI b8
primeRenderer2DGetAntiAliasing(primeRenderer2D* renderer);

PAPI b8
primeRenderer2DGetVsync(primeRenderer2D* renderer);
