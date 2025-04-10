
#pragma once

#include "defines.h"
#include "viewport.h"

struct prContext;
struct prRenderer;

struct prRect
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 w = 0.0f;
    f32 h = 0.0f;
};

PR_API prRenderer* prCreateRenderer(prContext* context, b8 use_ndc);
PR_API void prDestroyRenderer(prRenderer* renderer);

PR_API void prDrawRect(prRenderer* renderer, const prRect rect);

PR_API void prFlush(prRenderer* renderer);

