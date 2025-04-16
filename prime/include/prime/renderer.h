
#pragma once

#include "defines.h"
#include "viewport.h"
#include "color.h"
#include "rect.h"

/// @brief Renderer
struct prRenderer;

struct prContext;
struct prTexture;
struct prFont;

/// @brief Flips
enum prFlips_
{
    prFlips_None = 0,
    prFlips_Horizontal = PR_BIT(0),
    prFlips_Vertical = PR_BIT(1)
};

/// @brief Rotation anchors
enum prAnchors_
{
    prAnchors_TopLeft,
    prAnchors_Center
};

/// @brief camera
struct prCamera
{
    prViewport view;    
    f32 rotation = 0.0f;
};

/**
 * @brief Create a renderer. A Context must be bound before creating the renderer.
 * @returns If successful, a pointer to the created renderer otherwise nullptr.
 */
PR_API prRenderer* prCreateRenderer();

/**
 * @brief Destroy a renderer. A Context must be bound before destroying the renderer.
 * @param renderer The renderer
 */
PR_API void prDestroyRenderer(prRenderer* renderer);

/**
 * @brief Draw a rect using a renderer.
 * @param renderer The renderer
 * @param rect The rect
 * @param color The color
 */
PR_API void prRendererDrawRect(prRenderer* renderer, const prRect rect, const prColor color);

/**
 * @brief Draw a rect using a renderer.
 * @param renderer The renderer
 * @param rect The rect
 * @param rotation The angle degrees
 * @param anchor The rotation anchor
 * @param color The color
 */
PR_API void prRendererDrawRectEx(prRenderer* renderer, const prRect rect, f32 rotation, u32 anchor, const prColor color);

/**
 * @brief Draw a texture using a renderer.
 * @param renderer The renderer
 * @param rect The rect
 * @param texture The texture
 */
PR_API void prRendererDrawTexture(prRenderer* renderer, const prRect rect, prTexture* texture);

/**
 * @brief Draw a texture using a renderer.
 * @param renderer The renderer
 * @param rect The rect
 * @param rotation The angle degrees
 * @param anchor The rotation anchor
 * @param texture The texture
 * @param tint_color The tint_color
 * @param flip The flip
 */
PR_API void prRendererDrawTextureEx(prRenderer* renderer, const prRect rect, f32 rotation,
                                    u32 anchor, prTexture* texture, const prColor tint_color, u32 flip);


/**
 * @brief Draw a text using a renderer.
 * @param renderer The renderer
 * @param x The position x
 * @param y The position y
 * @param text The text
 * @param font The font
 * @param color The color
 */
PR_API void prRendererDrawText(prRenderer* renderer, f32 x, f32 y, f32 scale, const char* text, prFont* font, const prColor color);

/**
 * @brief Update the renderer
 * @param renderer The renderer
 */
PR_API void prRendererFlush(prRenderer* renderer);

/**
 * @brief Set the renderer camera
 * @param renderer The renderer
 * @param camera The camera
 */
PR_API void prSetRendererCamera(prRenderer* renderer, prCamera camera);