
#pragma once

#include "prime/maths.h"

struct primeWindow;
struct primeContext;

enum primeDrawMode
{
    PRIME_DRAW_MODE_TRIANGLES,
    PRIME_DRAW_MODE_LINES
};

enum primeDrawType
{
    PRIME_DRAW_TYPE_ARRAYS,
    PRIME_DRAW_TYPE_ELEMENTS
};

struct primeView
{
    primeVec2i pos;
    primeVec2u size;
};

PRIME_API primeContext* primeCreateContext(primeWindow* window);
PRIME_API void primeDestroyContext(primeContext* context);

PRIME_API void primeClear(primeContext* context);
PRIME_API void primePresent(primeContext* context);
PRIME_API void primeBindContext(primeContext* context);
PRIME_API void primeUnbindContext(primeContext* context);

PRIME_API void primeSubmit(primeContext* context, primeDrawType type, primeDrawMode mode, u32 count);
PRIME_API void primeSubmitInstanced(primeContext* context, primeDrawType type, primeDrawMode mode, u32 count, u32 instance_count);

PRIME_API void primeSetVsync(primeContext* context, b8 vsync);
PRIME_API void primeSetClearColor(primeContext* context, const primeVec4 color);
PRIME_API void primeSetClearColori(primeContext* context, const primeVec4u color);

PRIME_API void primeSetView(primeContext* context, const primeView view);
PRIME_API const primeView* primeGetView(primeContext* context);