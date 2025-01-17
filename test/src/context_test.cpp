
#include "prime/prime.h"

b8
contextTest()
{
	prLogInfo("");
	prLogInfo("Begin Context Test");

	PrDevice* device = prDeviceCreate(PrDriverTypeOpenGL);
	PrWindow* window = prWindowCreate("Prime Window", 640, 480);
	PrContext* context = prContextCreate(device, window);
	prContextSetClearColor(context, prColorFromf32(.2f, .2f, .2f, 1.0f));

	while (!prWindowShouldClose(window)) {
		prWindowPollEvents();

		prContextClear(device);
		prContextSwapbuffers(device);
	}

	prDeviceDestroy(device);
	prWindowDestroy(window);

	prLogInfo("End Context Test");
	prLogInfo("");
	return PR_PASSED;
}