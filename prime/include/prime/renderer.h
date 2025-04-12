
#pragma once

#include "defines.h"
#include "viewport.h"

struct prContext;
struct prTexture;
struct prRenderer;

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

struct prRendererDebugInfo
{
    u32 draw_calls = 0;
    u32 vertex_count = 0;
    u32 index_count = 0;
};

PR_API prRenderer* prCreateRenderer();
PR_API void prDestroyRenderer(prRenderer* renderer);

PR_API void prRendererDrawRect(prRenderer* renderer, const prRect rect);
PR_API void prRendererDrawTexture(prRenderer* renderer, const prRect rect);
PR_API void prRendererFlush(prRenderer* renderer);

PR_API void prSetRendererDrawColor(prRenderer* renderer, f32 r, f32 g, f32 b, f32 a);
PR_API void prSetRendererDrawColori(prRenderer* renderer, u8 r, u8 g, u8 b, u8 a);

PR_API void prSetRendererTintColor(prRenderer* renderer, f32 r, f32 g, f32 b, f32 a);
PR_API void prSetRendererTintColori(prRenderer* renderer, u8 r, u8 g, u8 b, u8 a);

PR_API void prSetRendererCamera(prRenderer* renderer, prCamera camera);
PR_API void prSetRendererTexture(prRenderer* renderer, prTexture* texture);

