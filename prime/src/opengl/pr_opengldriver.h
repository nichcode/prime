#pragma once

#include "pr_driver.h"

PrDriverContext*
prGLDriverContextCreate(PrWindow* window);

void
prGLDriverDestroy(PrDriverContext* driver_context);

void
prGLDriverSwapbuffers(PrWindow* window, PrDriverContext* driver_context);

void
prGLDriverMakeActive(PrWindow* window, PrDriverContext* driver_context);

void
prGLDriverSetClearColor(PrDriverContext* driver_context, const PrColor& color);

void
prGLDriverClear(PrDriverContext* driver_context);

void
prGLDriverMakeActive(PrWindow* window, PrDriverContext* driver_context);

void
prGLDriverSetVsync(PrDriverContext* driver_context, b8 vsync);
