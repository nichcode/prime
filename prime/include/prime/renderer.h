
#pragma once

#include "defines.h"
#include "viewport.h"
#include "color.h"

struct prContext;
struct prTexture;
struct prFont;
struct prRenderer;

enum prFlips_
{
    prFlips_None = 0,
    prFlips_Horizontal = PR_BIT(0),
    prFlips_Vertical = PR_BIT(1)
};

struct prRect
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 w = 0.0f;
    f32 h = 0.0f;
};

struct prCamera
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 aspect_ratio = 0.0f;
    f32 rotation = 0.0f;
    f32 zoom = 0.0f;
};

PR_API prRenderer* prCreateRenderer();
PR_API void prDestroyRenderer(prRenderer* renderer);

PR_API void prRendererDrawRect(prRenderer* renderer, const prRect rect, const prColor color);
PR_API void prRendererDrawRectEx(prRenderer* renderer, const prRect rect, f32 rotation, const prColor color);

PR_API void prRendererDrawTexture(prRenderer* renderer, const prRect rect, prTexture* texture);

PR_API void prRendererDrawTextureEx(prRenderer* renderer, const prRect rect, f32 rotation,
                                    prTexture* texture, const prColor tint_color, u32 flip);

PR_API void prRendererDrawText(prRenderer* renderer, f32 x, f32 y, f32 scale, const char* text, prFont* font, const prColor color);

PR_API void prRendererFlush(prRenderer* renderer);

PR_API void prSetRendererCamera(prRenderer* renderer, prCamera camera);