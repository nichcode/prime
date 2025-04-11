
#pragma once

#include "viewport.h"

struct prWindow;
struct prContext;

enum prContextTypes_
{
    prContextTypes_OpenGL
};

enum prDrawModes_
{
    prDrawModes_Triangles
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
PR_API void prSetClearColori(u8 r, u8 g, u8 b, u8 a);
PR_API void prSetView(prViewport viewport);

PR_API void prDrawArrays(u32 mode, u32 count);
PR_API void prDrawElements(u32 mode, u32 count);
PR_API void prDrawElementsInstanced(u32 mode, u32 count, u32 instance_count);
PR_API void prDrawArraysInstanced(u32 mode, u32 count, u32 instance_count);

PR_API prViewport prGetView();
