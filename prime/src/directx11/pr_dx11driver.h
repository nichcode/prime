#pragma once

#include "pr_driver.h"

PrDriverContext*
prDx11DriverContextCreate(PrWindow* window);

void
prDx11DriverDestroy(PrDriverContext* driver_context);

void
prDx11DriverSwapbuffers(PrWindow* window, PrDriverContext* driver_context);

void
prDx11DriverMakeActive(PrWindow* window, PrDriverContext* driver_context);

void
prDx11DriverSetClearColor(PrDriverContext* driver_context, const PrColor& color);

void
prDx11DriverClear(PrDriverContext* driver_context);

void
prDx11DriverMakeActive(PrWindow* window, PrDriverContext* driver_context);

void
prDx11DriverSetVsync(PrDriverContext* driver_context, b8 vsync);

