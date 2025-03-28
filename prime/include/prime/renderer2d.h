
#pragma once

#include "prime/rect.h"
#include "prime/maths.h"

struct primeContext;
struct primeTexture;
struct primeSubTexture;
struct primeRenderer2D;

PRIME_API primeRenderer2D* primeCreateRenderer2D(primeContext* context);
PRIME_API void primeDestroyRenderer2D(primeRenderer2D* renderer);

PRIME_API void primeDrawRect(primeRenderer2D* renderer, const primeRect rect);
PRIME_API void primeDrawTexture(primeRenderer2D* renderer, const primeVec2 pos);

PRIME_API void primeDrawSubTexture(primeRenderer2D* renderer, primeSubTexture* sub_texture, const primeVec2 pos);
PRIME_API void primeDrawText(primeRenderer2D* renderer, const char* text, const primeVec2 pos);

PRIME_API void primeSetTexture(primeRenderer2D* renderer, primeTexture* texture);
PRIME_API void primeSetFont(primeRenderer2D* renderer, primeFont* font);
PRIME_API void primeFlush(primeRenderer2D* renderer);

PRIME_API void primeSetFontScale(primeRenderer2D* renderer, f32 scale);
PRIME_API void primeSetTextureScale(primeRenderer2D* renderer, f32 scale);

PRIME_API void primeSetDrawColor(primeRenderer2D* renderer, const primeVec4 color);
PRIME_API void primeSetDrawColori(primeRenderer2D* renderer, const primeVec4u color);

PRIME_API void primeSetTintColor(primeRenderer2D* renderer, const primeVec4 color);
PRIME_API void primeSetTintColori(primeRenderer2D* renderer, const primeVec4u color);

PRIME_API void primeSetTextColor(primeRenderer2D* renderer, const primeVec4 color);
PRIME_API void primeSetTextColori(primeRenderer2D* renderer, const primeVec4u color);
