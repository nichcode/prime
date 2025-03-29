
#pragma once

#include "prime/rect.h"
#include "prime/vec4.h"
#include "prime/vec4i.h"

struct primeContext;
struct primeTexture;
struct primeRenderer2D;

using primeAnchor = u32;
using primeFlip = u32;

enum primeAnchors_
{
    primeAnchors_TopLeft,
    primeAnchors_Center
};

enum primeFlips_
{
    primeFlips_None = 0,
    primeFlips_X = PRIME_BIT(0),
    primeFlips_Y = PRIME_BIT(1)
};

PRIME_API primeRenderer2D* primeCreateRenderer2D(primeContext* context);
PRIME_API void primeDestroyRenderer2D(primeRenderer2D* renderer);

PRIME_API void primeDrawRect(primeRenderer2D* renderer, const primeRect rect);
PRIME_API void primeDrawRectEx(primeRenderer2D* renderer, const primeRect rect, f32 rotation);

PRIME_API void primeDrawTexture(primeRenderer2D* renderer, const primeVec2 pos);
PRIME_API void primeDrawTextureEx(primeRenderer2D* renderer, const primeVec2 pos, f32 rotation, primeFlip flip);

PRIME_API void primeDrawSubTexture(primeRenderer2D* renderer, f32 x, f32 y, f32 w, f32 h, const primeVec2 pos);
PRIME_API void primeDrawSubTextureEx(primeRenderer2D* renderer, f32 x, f32 y, f32 w, f32 h, const primeVec2 pos, f32 rotation, primeFlip flip);

PRIME_API void primeDrawText(primeRenderer2D* renderer, const char* text, const primeVec2 pos);
PRIME_API void primeDrawTextEx(primeRenderer2D* renderer, const char* text, const primeVec2 pos, primeFlip flip);

PRIME_API void primeSetAnchor(primeRenderer2D* renderer, primeAnchor anchor);
PRIME_API void primeSetTexture(primeRenderer2D* renderer, primeTexture* texture);

PRIME_API void primeSetFont(primeRenderer2D* renderer, primeFont* font);
PRIME_API void primeFlush(primeRenderer2D* renderer);

PRIME_API void primeSetFontScale(primeRenderer2D* renderer, f32 scale);
PRIME_API void primeSetTextureScale(primeRenderer2D* renderer, f32 scale);

PRIME_API void primeSetDrawColor(primeRenderer2D* renderer, const primeVec4 color);
PRIME_API void primeSetDrawColori(primeRenderer2D* renderer, const primeVec4i color);

PRIME_API void primeSetTintColor(primeRenderer2D* renderer, const primeVec4 color);
PRIME_API void primeSetTintColori(primeRenderer2D* renderer, const primeVec4i color);

PRIME_API void primeSetTextColor(primeRenderer2D* renderer, const primeVec4 color);
PRIME_API void primeSetTextColori(primeRenderer2D* renderer, const primeVec4i color);
