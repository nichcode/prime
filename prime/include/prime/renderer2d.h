
#pragma once

#include "prime/rect.h"
#include "prime/maths.h"

struct primeContext;
struct primeTexture;
struct primeRenderer2D;

PRIME_API primeRenderer2D* primeCreateRenderer2D(primeContext* context);
PRIME_API void primeDestroyRenderer2D(primeRenderer2D* renderer);

PRIME_API void primeRenderer2DDrawRect(primeRenderer2D* renderer, const primeRect rect);
PRIME_API void primeRenderer2DDrawTexture(primeRenderer2D* renderer, const primeVec2 pos);
PRIME_API void primeRenderer2DDrawText(primeRenderer2D* renderer, const char* text, const primeVec2 pos);

PRIME_API void primeRenderer2DSetTexture(primeRenderer2D* renderer, primeTexture* texture);
PRIME_API void primeRenderer2DSetFont(primeRenderer2D* renderer, primeFont* font);
PRIME_API void primeRenderer2DFlush(primeRenderer2D* renderer);

PRIME_API void primeRenderer2DSetFontScale(primeRenderer2D* renderer, f32 scale);
PRIME_API void primeRenderer2DSetTextureScale(primeRenderer2D* renderer, f32 scale);

PRIME_API void primeRenderer2DSetDrawColor(primeRenderer2D* renderer, const primeVec4 color);
PRIME_API void primeRenderer2DSetDrawColori(primeRenderer2D* renderer, const primeVec4u color);

PRIME_API void primeRenderer2DSetTintColor(primeRenderer2D* renderer, const primeVec4 color);
PRIME_API void primeRenderer2DSetTintColori(primeRenderer2D* renderer, const primeVec4u color);

PRIME_API void primeRenderer2DSetTextColor(primeRenderer2D* renderer, const primeVec4 color);
PRIME_API void primeRenderer2DSetTextColori(primeRenderer2D* renderer, const primeVec4u color);
