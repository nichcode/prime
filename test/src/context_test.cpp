
#include "prime/prime.h"

b8
contextTestGL()
{
	prLogInfo("");
	prLogInfo("Begin Context Test GL");

	PrWindow* window = prWindowCreate("Prime Window GL", 640, 480);
	PrDevice* device = prDeviceCreate(PrDriverTypeOpenGL, window);

	prDeviceMakeActive(device);
	prDeviceSetClearColor(device, prColorFromF32(.2f, .2f, .2f, 1.0f));
	prDeviceSetVsync(device, true);

	while (!prWindowShouldClose(window)) {
		prWindowPollEvents();

		prDeviceClear(device);
		prDeviceSwapbuffers(device);
	}

	prDeviceDestroy(device);
	prWindowDestroy(window);

	prLogInfo("End Context Test GL");
	prLogInfo("");
	return PR_PASSED;
}

b8
contextTestDx11()
{
	prLogInfo("");
	prLogInfo("Begin Context Test Dx11");

	PrWindow* window = prWindowCreate("Prime Window Dx11", 640, 480);
	PrDevice* device = prDeviceCreate(PrDriverTypeDirectX11, window);
	prDeviceSetClearColor(device, prColorFromF32(.2f, .2f, .2f, 1.0f));

	prDeviceMakeActive(device);
	prDeviceSetVsync(device, true);

	while (!prWindowShouldClose(window)) {
		prWindowPollEvents();

		prDeviceClear(device);
		prDeviceSwapbuffers(device);
	}

	prDeviceDestroy(device);
	prWindowDestroy(window);

	prLogInfo("End Context Test Dx11");
	prLogInfo("");
	return PR_PASSED;
}

b8
multiContextTest()
{
	prLogInfo("");
	prLogInfo("Begin Multi Context Test");

	// dx11
	PrWindow* window_dx11 = prWindowCreate("Prime Window Dx11", 640, 480);
	PrDevice* device_dx11 = prDeviceCreate(PrDriverTypeDirectX11, window_dx11);
	prDeviceSetClearColor(device_dx11, prColorFromF32(.2f, .2f, .2f, 1.0f));
	prDeviceMakeActive(device_dx11);
	prDeviceSetVsync(device_dx11, true);

	// gl
	PrWindow* window_gl = prWindowCreate("Prime Window GL", 640, 480);
	PrDevice* device_gl = prDeviceCreate(PrDriverTypeOpenGL, window_gl);
	prDeviceSetClearColor(device_gl, prColorFromF32(.2f, .2f, .2f, 1.0f));
	prDeviceMakeActive(device_gl);
	prDeviceSetVsync(device_gl, true);

	while (!prWindowShouldClose(window_dx11)) {
		prWindowPollEvents();

		// dx11
		prDeviceClear(device_dx11);
		prDeviceSwapbuffers(device_dx11);
		
		// gl
		prDeviceClear(device_gl);
		prDeviceSwapbuffers(device_gl);
	}

	// dx11
	prDeviceDestroy(device_dx11);
	prWindowDestroy(window_dx11);

	// gl
	prDeviceDestroy(device_gl);
	prWindowDestroy(window_gl);

	prLogInfo("End Multi Context Test");
	prLogInfo("");
	return PR_PASSED;
}