
#include "prime/pr_device.h"
#include "pr_types.h"
#include "prime/pr_context.h"

#ifdef PR_PLATFORM_WINDOWS
#include "windows/pr_wglcontext.h"
#endif // PR_PLATFORM_WINDOWS

static b8 s_GLInit = false;

PrDevice*
prDeviceCreate(PrDriverType driver_type)
{
	PrDevice* device = (PrDevice*)prMemAlloc(sizeof(PrDevice));
	device->type = driver_type;
	if (driver_type == PrDriverTypeOpenGL) {
#ifdef PR_PLATFORM_WINDOWS
		prWGLContextCreateDummy();
#endif // PR_PLATFORM_WINDOWS
		s_GLInit = true;
	}
	return device;
}

void
prDeviceDestroy(PrDevice* device)
{
	PR_ASSERT_MSG(device, "Device is null");
	// context
	for (PrContext* context : device->contexts)
	{
		prContextDestroy(context);
	}
	device->contexts.clear();
	prMemFree(device, sizeof(PrDevice));
	device = nullptr;
}