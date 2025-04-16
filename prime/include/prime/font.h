
#pragma once

#include "defines.h"

struct prTexture;

/// @brief Font
struct prFont;

/// @brief Font Glyph
struct prGlyph
{
    /// @brief The x index of the glyph
    f32 index_x = 0.0f;

    /// @brief The y index of the glyph
    f32 index_y = 0.0f;

    /// @brief The x offset of the glyph
    f32 offset_x = 0.0f;
    
    /// @brief The y offset of the glyph
    f32 offset_y = 0.0f;

    /// @brief The width of the glyph
    f32 width = 0.0f;
    
    /// @brief The height of the glyph
    f32 height = 0.0f;

    /// @brief The x advance of the glyph
    u32 advance_x = 0;
    
    /// @brief The y advance of the glyph
    u32 advance_y = 0;
};

/**
 * @brief Load a font from disk. A Context must be bound before loading the buffer.
 * @param file The filepath of the font
 * @param size The size of the font
 * @returns If successful, a pointer to the created font otherwise nullptr.
 */
PR_API prFont* prLoadFont(const char* filepath, u32 size);

/**
 * @brief Destroy a font. A Context must be bound before destroying the font.
 * @param font The font to be destroyed
 */
PR_API void prDestroyFont(prFont* font);

/**
 * @brief Get the size of a font.
 * @param font The font to query its size
 * @returns The size of the specified font
 */
PR_API u32 prGetFontSize(prFont* font);

/**
 * @brief Get the filepath of a font.
 * @param font The font to query its filepath
 * @returns The filepath of the specified font
 */
PR_API const char* prGetFontPath(prFont* font);

/**
 * @brief Get the baseline of a font.
 * @param font The font to query its baseline
 * @returns The filepath of the specified font
 */
PR_API f32 prGetFontBaseLine(prFont* font);

/**
 * @brief Get the texture atlas of a font.
 * @param font The font to query its texture atlas
 * @returns The filepath of the specified font
 */
PR_API prTexture* prGetFontTexture(prFont* font);

/**
 * @brief Get a glyph of a font.
 * @param font The font to query its glyph
 * @param c The index of the glyph
 * @returns If successful, a pointer to the glyph otherwise nullptr.
 */
PR_API prGlyph* prGetFontGlyph(prFont* font, u8 c);

