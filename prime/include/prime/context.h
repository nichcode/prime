
#pragma once

#include "defines.h"

struct prWindow;
struct prContext;

enum prContextTypes_
{
    prContextTypes_OpenGL
};

struct prContextDesc
{
    u32 type;
    u32 major;
    u32 minor;
};

PR_API prContext* prCreateContext(prWindow* window, prContextDesc desc);
PR_API void prDestroyContext(prContext* context);
PR_API void prSwapBuffers();
PR_API void prClear();

PR_API void prMakeActive(prContext* context, b8 bind_pipeline);
PR_API void prSetVsync(b8 vsync);
PR_API void prSetClearColor(f32 r, f32 g, f32 b, f32 a);
