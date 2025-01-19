
#include "prime/prime.h"

b8
contextTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Context Test GL");

	prime_Window* window = prime_CreateWindow("Prime Window GL", 640, 480);
	prime_Device* device = prime_CreateDevice(prime_DeviceTypeGL, window);

	prime_MakeActive(device);
	prime_SetClearColor(device, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_SetVsync(device, true);

	while (!prime_WindowShouldClose(window)) {
		prime_PollEvents();

		prime_Clear(device);
		prime_Swapbuffers(device);
	}

	prime_DestroyDevice(device);
	prime_DestroyWindow(window);

	prime_LogInfo("End Context Test GL");
	prime_LogInfo("");
	return PRIME_PASSED;
}

b8
contextTestDx11()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Context Test Dx11");

	prime_Window* window = prime_CreateWindow("Prime Window Dx11", 640, 480);
	prime_Device* device = prime_CreateDevice(prime_DeviceTypeDx11, window);
	prime_SetClearColor(device, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));

	prime_MakeActive(device);
	prime_SetVsync(device, true);

	while (!prime_WindowShouldClose(window)) {
		prime_PollEvents();

		prime_Clear(device);
		prime_Swapbuffers(device);
	}

	prime_DestroyDevice(device);
	prime_DestroyWindow(window);

	prime_LogInfo("End Context Test Dx11");
	prime_LogInfo("");
	return PRIME_PASSED;
}

b8
multiContextTest()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Multi Context Test");

	// dx11
	prime_Window* window_dx11 = prime_CreateWindow("Prime Window Dx11", 640, 480);
	prime_Device* device_dx11 = prime_CreateDevice(prime_DeviceTypeDx11, window_dx11);
	prime_SetClearColor(device_dx11, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_MakeActive(device_dx11);
	prime_SetVsync(device_dx11, true);

	// gl
	prime_Window* window_gl = prime_CreateWindow("Prime Window GL", 640, 480);
	prime_Device* device_gl = prime_CreateDevice(prime_DeviceTypeGL, window_gl);
	prime_SetClearColor(device_gl, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_MakeActive(device_gl);
	prime_SetVsync(device_gl, true);

	while (!prime_WindowShouldClose(window_dx11)) {
		prime_PollEvents();

		// dx11
		prime_Clear(device_dx11);
		prime_Swapbuffers(device_dx11);
		
		// gl
		prime_Clear(device_gl);
		prime_Swapbuffers(device_gl);
	}

	// dx11
	prime_DestroyDevice(device_dx11);
	prime_DestroyWindow(window_dx11);

	// gl
	prime_DestroyDevice(device_gl);
	prime_DestroyWindow(window_gl);

	prime_LogInfo("End Multi Context Test");
	prime_LogInfo("");
	return PRIME_PASSED;
}