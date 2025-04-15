
#pragma once

#include "pch.h"
#include "prime/font.h"

prFont* prLoadFont(const char* filepath, u32 size)
{
    FT_Face font_face;
    i32 error = FT_New_Face(s_Library, filepath, 0, &font_face);
    if (error == FT_Err_Unknown_File_Format) {
        PR_ASSERT(false, "Unknown file format"); 
    }
    else if (error != 0) {
        PR_ASSERT(false, "filepath is null"); 
    }

    FT_Set_Pixel_Sizes(font_face, 0, size);
    u32 padding = 2;
    u32 row = 0;
    u32 col = padding;
    static u32 texture_size = 512;
    char buffer[texture_size  * texture_size];

    PR_ASSERT(s_ActiveContext, "no context bound");
    prFont* font = new prFont();
    PR_ASSERT(font, "failed to create font");

    FT_GlyphSlot slot =  font_face->glyph;

    for (u8 c = 32; c < 127; c++) {
        if (FT_Load_Char(font_face, c, FT_LOAD_RENDER)) {
            PR_ERROR("Failed to load Glyph");
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

        prGlyph glyph;
        glyph.index_x = (f32)col;
        glyph.index_y = (f32)row;

        glyph.offset_x = (f32)slot->bitmap_left;
        glyph.offset_y = (f32)slot->bitmap_top;

        glyph.size_x = (f32)slot->bitmap.width;
        glyph.size_y = (f32)slot->bitmap.rows;

        glyph.advance_x = (u32)slot->advance.x >> 6;
        glyph.advance_y = (u32)slot->advance.y >> 6;

        font->glyphs.insert(std::pair<u8, prGlyph>(c, glyph));
        col += slot->bitmap.width + padding;
    }

    prTextureDesc desc;
    desc.flag = prTextureFlags_Storage;
    desc.storage_data = (char*)buffer;
    desc.format = prTextureFormats_R8;
    desc.width = texture_size;
    desc.height = texture_size;
    font->texture = prCreateTexture(desc);

    font->path = filepath;
    font->size = size;
    font->baseline = font->glyphs.at('H').offset_y;
    FT_Done_Face(font_face);

    s_ActiveContext->data.fonts.push_back(font);
    return font;
}

void prDestroyFont(prFont* font)
{
    PR_ASSERT(font, "font is null");
    PR_ASSERT(s_ActiveContext, "no context bound");
    prContext* context = s_ActiveContext;

    auto it = std::find(context->data.fonts.begin(), context->data.fonts.end(), font);
    if (it != context->data.fonts.end()) {
        context->data.fonts.erase(it); 
    }

    font->glyphs.clear();
    delete font;
    font = nullptr;
}

u32 prGetFontSize(prFont* font)
{
    PR_ASSERT(font, "font is null");
    return font->size;
}

const char* prGetFontPath(prFont* font)
{
    PR_ASSERT(font, "font is null");
    return font->path;
}

f32 prGetFontBaseLine(prFont* font)
{
    PR_ASSERT(font, "font is null");
    return font->baseline;
}

prTexture* prGetFontTexture(prFont* font)
{
    PR_ASSERT(font, "font is null");
    return font->texture;
}

prGlyph* prGetFontGlyph(prFont* font, u8 c)
{
    PR_ASSERT(font, "font is null");
    return &font->glyphs.at(c);
}