
#pragma once

#include "rect.h"

/// @brief Texture
struct prTexture;

/// @brief Texture flags
enum prTextureFlags_
{
    prTextureFlags_None,
    prTextureFlags_Target,
    prTextureFlags_Storage
};

/// @brief Texture formats
enum prTextureFormats_
{
    prTextureFormats_R8,
    prTextureFormats_RGB8,
    prTextureFormats_RGB16,
    prTextureFormats_RGB16F,
    prTextureFormats_RGB32F,
    prTextureFormats_RGBA8,
    prTextureFormats_RGBA16,
    prTextureFormats_RGBA16F,
    prTextureFormats_RGBA32F
};

/// @brief Texture descriptor
struct prTextureDesc
{
    /// @brief texure flags. Choose from prTextureFlags_
    u32 flag = 0;

    /// @brief texure format. Choose from prTextureFormats_
    u32 format = 0;

    /// @brief width of the texture.
    u32 width = 1;

    /// @brief width of the texture.
    u32 height = 1;
    
    /// @brief texure storage data. This is for storage textures.
    void* storage_data = nullptr;
};

/**
 * @brief Create a texture with a texture descriptor struct.
 * A Context must be bound before creating the texture.
 * @param desc The texture descriptor
 * @returns If successful, a pointer to the created texture otherwise nullptr.
 */
PR_API prTexture* prCreateTexture(prTextureDesc desc);

/**
 * @brief Load a texture from disk.
 * A Context must be bound before creating the texture.
 * @param filepath The filepath
 * @returns If successful, a pointer to the created texture otherwise nullptr.
 */
PR_API prTexture* prLoadTexture(const char* filepath);

/**
 * @brief Destroy a texture. A Context must be bound before destroying the texture.
 * @param texture The texture
 */
PR_API void prDestroyTexture(prTexture* texture);

/**
 * @brief bind a texture to the pipeline
 * @param texture The texture
 * @param slot The slot to bind the texture to
 */
PR_API void prBindTexture(prTexture* texture, u32 slot);

/**
 * @brief Bind a render Target.
 * The texture must be a render target. ie. prTextureFlags_Target
 * @param texture The texture
 */
PR_API void prBindTarget(prTexture* texture);

/**
 * @brief Unbind a render Target.
 * The texture must be a render target. ie. prTextureFlags_Target
 * @param texture The texture
 */
PR_API void prUnbindTarget(prTexture* texture);

/**
 * @brief Get the width of a texture.
 * @param texture The texture
 * @returns the width of the texture
 */
PR_API u32 prGetTextureWidth(prTexture* texture);

/**
 * @brief Get the height of a texture.
 * @param texture The texture
 * @returns the height of the texture
 */
PR_API u32 prGetTextureHeight(prTexture* texture);

/**
 * @brief Get the filepath of a texture.
 * @param texture The texture
 * @returns the filepath of the texture
 */
PR_API const char* prGetTexturePath(prTexture* texture);

/**
 * @brief Get the rect of a texture.
 * @param texture The texture
 * @returns the rect of the texture
 */
PR_API prRect prGetTextureRect(prTexture* texture);