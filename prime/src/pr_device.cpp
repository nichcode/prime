
#include "prime/pr_device.h"
#include "pr_driver.h"
#include "prime/pr_memory.h"
#include "pr_platform.h"

struct PrDevice
{
	PrDriverType type;
	PrDriver* driver = nullptr;
	b8 vSync = false;
};

PrDevice*
prDeviceCreate(PrDriverType driver_type, PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	PR_ASSERT_MSG(!prPlatformWin32HasContext(window), "Window already has context");

	PrDevice* device = (PrDevice*)prMemAlloc(sizeof(PrDevice));
	device->driver = prDriverCreate(driver_type, window);
	device->type = driver_type;
	return device;
}

void
prDeviceDestroy(PrDevice* device)
{
	PR_ASSERT_MSG(device, "Device is null");
	prDriverDestroy(device->driver);
	prMemFree(device, sizeof(PrDevice));
	device = nullptr;
}

void
prDeviceSwapbuffers(PrDevice* device)
{
	PR_ASSERT_MSG(device, "Device is null");
	prDriverSwapbuffers(device->driver);
}

void
prDeviceSetClearColor(PrDevice* device, const PrColor& color)
{
	PR_ASSERT_MSG(device, "Device is null");
	prDriverSetClearColor(device->driver, color);
}

void
prDeviceClear(PrDevice* device)
{
	PR_ASSERT_MSG(device, "Device is null");
	prDriverClear(device->driver);
}

void
prDeviceMakeActive(PrDevice* device)
{
	PR_ASSERT_MSG(device, "Device is null");
	prDriverMakeActive(device->driver);
}

void
prDeviceSetVsync(PrDevice* device, b8 vsync)
{
	PR_ASSERT_MSG(device, "Device is null");
	prDriverSetVsync(device->driver, vsync);
	device->vSync = true;
}