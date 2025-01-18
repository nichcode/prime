#pragma once

#include "prime/pr_device.h"

struct PrWindow;
struct PrContext;

struct PrDriver;
struct PrDriverContext;

using PrDriverDestroyFunc = void(*)(PrDriverContext* driver_context);
using PrDriverSwapbuffersFunc = void(*)(PrWindow* window, PrDriverContext* driver_context);
using PrDriverSetClearColorFunc = void(*)(PrDriverContext* driver_context, const PrColor& color);
using PrDriverClearFunc = void(*)(PrDriverContext* driver_context);
using PrDriverMakeActiveFunc = void(*)(PrWindow* window, PrDriverContext* driver_context);
using PrDriverSetVsyncFunc = void(*)(PrDriverContext* driver_context, b8 vsync);

PrDriver*
prDriverCreate(PrDriverType type, PrWindow* window);

void
prDriverDestroy(PrDriver* driver);

void
prDriverSwapbuffers(PrDriver* driver);

void
prDriverSetClearColor(PrDriver* driver, const PrColor& color);

void
prDriverClear(PrDriver* driver);

void
prDriverMakeActive(PrDriver* driver);

void
prDriverSetVsync(PrDriver* driver, b8 vsync);