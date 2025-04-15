
#pragma once

#include "defines.h"
#include "viewport.h"
#include "color.h"
#include "rect.h"

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

enum prAnchors_
{
    prAnchors_TopLeft,
    prAnchors_Center
};

struct prCamera
{
    prViewport view;    
    f32 rotation = 0.0f;
};

PR_API prRenderer* prCreateRenderer();
PR_API void prDestroyRenderer(prRenderer* renderer);

PR_API void prRendererDrawRect(prRenderer* renderer, const prRect rect, const prColor color);
PR_API void prRendererDrawRectEx(prRenderer* renderer, const prRect rect, f32 rotation, u32 anchor, const prColor color);

PR_API void prRendererDrawTexture(prRenderer* renderer, const prRect rect, prTexture* texture);
PR_API void prRendererDrawTextureEx(prRenderer* renderer, const prRect rect, f32 rotation,
                                    u32 anchor, prTexture* texture, const prColor tint_color, u32 flip);

PR_API void prRendererDrawText(prRenderer* renderer, f32 x, f32 y, f32 scale, const char* text, prFont* font, const prColor color);

PR_API void prRendererFlush(prRenderer* renderer);
PR_API void prSetRendererCamera(prRenderer* renderer, prCamera camera);