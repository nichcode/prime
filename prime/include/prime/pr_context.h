#pragma once

#include "pr_defines.h"
#include "pr_color.h"

struct PrDevice;
struct PrContext;
struct PrWindow;

PR_API PrContext*
prContextCreate(PrDevice* device, PrWindow* window);

PR_API void
prContextDestroy(PrContext* context);

PR_API void
prContextSwapbuffers(PrDevice* device);

PR_API void
prContextSetClearColor(PrContext* context, const PrColor& color);

PR_API void
prContextClear(PrDevice* device);
