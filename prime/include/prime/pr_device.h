#pragma once

#include "pr_color.h"

struct PrDevice;
struct PrWindow;

enum PrDriverType
{
#ifdef PR_PLATFORM_WINDOWS
	PrDriverTypeDirectX11,
	PrDriverTypeOpenGL,
#endif // PR_PLATFORM_WINDOWS
};

PR_API PrDevice*
prDeviceCreate(PrDriverType driver_type, PrWindow* window);

PR_API void
prDeviceDestroy(PrDevice* device);

PR_API void
prDeviceSwapbuffers(PrDevice* device);

PR_API void
prDeviceSetClearColor(PrDevice* context, const PrColor& color);

PR_API void
prDeviceClear(PrDevice* device);

PR_API void
prDeviceMakeActive(PrDevice* device);

PR_API void
prDeviceSetVsync(PrDevice* device, b8 vsync);