
#include "prime/prime.h"

b8
contextTestGL()
{
	primeDevice* device = primeDeviceCreate(primeDeviceTypeGL);
	primeWindow* window = primeWindowCreate("Context TestGL", 640, 480);
	primeContext* context = primeContextCreate(device, window);

	primeContextMakeActive(context);
    primeColor color = primeColorFromF32(.2f, .2f, .2f, 1.0f);
	primeContextSetClearColor(context, &color);
	primeContextSetVsync(context, true);

	while (!primeWindowShouldClose(window)) {
		primeWindowPollEvents();

		primeContextClear(context);
		primeContextSwapbuffers(context);
	}

	primeDeviceDestroy(device);
	primeWindowDestroy(window);

    return true;
}
