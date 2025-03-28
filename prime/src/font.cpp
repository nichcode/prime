
#include "pch.h"
#include "prime/font.h"
#include "prime/texture.h"

#include "ft2build.h"
#include FT_FREETYPE_H

struct primeFont
{
    primeTexture* texture = nullptr;
    std::map<u8, primeGlyph> glyphs;
    const char* path = nullptr;
    u32 size = 0;
    f32 baseline = 0.0f;
};

primeFont* primeLoadFont(const char* filepath, u32 size)
{
    FT_Library library;
    int success = FT_Init_FreeType(&library);
    PRIME_ASSERT_MSG(!success, "Freetype initialization failed!");

    FT_Face font_face;
    i32 error = FT_New_Face(library, filepath, 0, &font_face);
    if (error == FT_Err_Unknown_File_Format) {
        PRIME_ASSERT_MSG(false, "Unknown file format"); 
    }
    else if (error != 0) {
        PRIME_ASSERT_MSG(false, "filepath is null"); 
    }

    FT_Set_Pixel_Sizes(font_face, 0, size);
    u32 padding = 2;
    u32 row = 0;
    u32 col = padding;
    static u32 texture_size = 512;
    char buffer[texture_size  * texture_size];
    primeFont* font = new primeFont();
    FT_GlyphSlot slot =  font_face->glyph;

    for (u8 c = 32; c < 127; c++) {
        if (FT_Load_Char(font_face, c, FT_LOAD_RENDER)) {
            PRIME_ERROR("Failed to load Glyph");
            continue;
        }

        FT_Render_Glyph(slot, FT_RENDER_MODE_SDF);

        if (col + slot->bitmap.width + padding >= texture_size) {
            col = padding;
            row += size;
        }

        for (u32 y = 0; y < slot->bitmap.rows; ++y) {
            for (u32 x = 0; x < slot->bitmap.width; ++x) {
            buffer[(row + y) * texture_size + col + x] =
                slot->bitmap.buffer[y * slot->bitmap.width + x];
            }
        }

        primeGlyph glyph;
        glyph.index = { col, row };
        glyph.advance.x = (u32)slot->advance.x >> 6;
        glyph.advance.y = (u32)slot->advance.y >> 6;
        glyph.offset.x = (f32)slot->bitmap_left,
        glyph.offset.y = (f32)slot->bitmap_top,
        glyph.size.x = slot->bitmap.width;
        glyph.size.y = slot->bitmap.rows;
        font->glyphs.insert(std::pair<u8, primeGlyph>(c, glyph));

        col += slot->bitmap.width + padding;
    }

    primeTextureDesc desc;
    desc.flag = primeTextureFlags_Storage;  
    desc.size = {texture_size, texture_size};
    desc.format = primeTextureFormat_R8;
    desc.data = (char*)buffer;
    font->texture = primeCreateTexture(desc);
    font->path = filepath;
    font->size = size;
    font->baseline = font->glyphs.at('H').offset.y;

    FT_Done_Face(font_face);
    FT_Done_FreeType(library);

    s_InitData.fonts.push_back(font);
    return font;
}

void primeDestroyFont(primeFont* font)
{
    PRIME_ASSERT_MSG(font, "font is null");
    auto it = std::find(s_InitData.fonts.begin(), s_InitData.fonts.end(), font);
    if (it != s_InitData.fonts.end()) {
        s_InitData.fonts.erase(it); 
    }
    _primeDeleteFont(font);
}

void _primeDeleteFont(primeFont* font)
{
    font->glyphs.clear();
    delete font;
    font = nullptr;
}

u32 primeGetFontSize(primeFont* font)
{
    PRIME_ASSERT_MSG(font, "font is null");
    return font->size;
}

const char* primeGetFontPath(primeFont* font)
{
    PRIME_ASSERT_MSG(font, "font is null");
    return font->path;
}

f32 primeGetFontBaseLine(primeFont* font)
{
    PRIME_ASSERT_MSG(font, "font is null");
    return font->baseline;
}

primeTexture* primeGetFontTexture(primeFont* font)
{
    PRIME_ASSERT_MSG(font, "font is null");
    return font->texture;
}

primeGlyph primeGetFontGlyph(primeFont* font, u8 c)
{
    PRIME_ASSERT_MSG(font, "font is null");
    return font->glyphs.at(c);
}