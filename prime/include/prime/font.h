
#pragma once

#include "defines.h"

struct prFont;
struct prTexture;

struct prGlyph
{
    f32 index_x = 0.0f;
    f32 index_y = 0.0f;
    f32 offset_x = 0.0f;
    f32 offset_y = 0.0f;
    f32 size_x = 0.0f;
    f32 size_y = 0.0f;
    u32 advance_x = 0;
    u32 advance_y = 0;
};

PR_API prFont* prLoadFont(const char* filepath, u32 size);
PR_API void prDestroyFont(prFont* font);

PR_API u32 prGetFontSize(prFont* font);
PR_API const char* prGetFontPath(prFont* font);
PR_API f32 prGetFontBaseLine(prFont* font);

PR_API prTexture* prGetFontTexture(prFont* font);
PR_API prGlyph* prGetFontGlyph(prFont* font, u8 c);

