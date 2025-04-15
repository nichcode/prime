
#pragma once

#include "viewport.h"
#include "color.h"

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

enum prBlendModes_
{
    prBlendModes_None,
    prBlendModes_Alpha
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
PR_API void prClear(const prColor color);

PR_API void prMakeActive(prContext* context);
PR_API void prSetVsync(b8 vsync);
PR_API void prSetView(prViewport viewport);
PR_API void prSetBlendMode(u32 blend_mode);

PR_API void prDrawArrays(u32 mode, u32 count);
PR_API void prDrawElements(u32 mode, u32 count);
PR_API void prDrawElementsInstanced(u32 mode, u32 count, u32 instance_count);
PR_API void prDrawArraysInstanced(u32 mode, u32 count, u32 instance_count);

PR_API prViewport prGetView();
