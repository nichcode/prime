
#pragma once

#include "prime/maths.h"

struct primeFont;
struct primeTexture;

struct primeGlyph
{
    primeVec2u index;
    primeVec2 offset;
    primeVec2u advance;
    primeVec2u size;
};

PRIME_API primeFont* primeLoadFont(const char* filepath, u32 size);
PRIME_API void primeDestroyFont(primeFont* font);

PRIME_API u32 primeGetFontSize(primeFont* font);
PRIME_API const char* primeGetFontPath(primeFont* font);
PRIME_API f32 primeGetFontBaseLine(primeFont* font);

PRIME_API primeTexture* primeGetFontTexture(primeFont* font);
PRIME_API primeGlyph primeGetFontGlyph(primeFont* font, u8 c);

