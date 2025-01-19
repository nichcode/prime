
#include "tests.h"

b8
contextTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Context Test GL");

	prime_Device* device = prime_CreateDevice(prime_DeviceTypeGL);
	prime_Window* window = prime_CreateWindow("Begin Context Test GL", 640, 480);
	prime_Context* context = prime_CreateContext(device, window);

	prime_MakeActive(context);
	prime_SetClearColor(context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_SetVsync(context, true);

	while (!prime_WindowShouldClose(window)) {
		prime_PollEvents();

		prime_Clear(context);
		prime_Swapbuffers(context);
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

	prime_Window* window = prime_CreateWindow("Begin Context Test Dx11", 640, 480);
	prime_Device* device = prime_CreateDevice(prime_DeviceTypeGL);
	prime_Context* context = prime_CreateContext(device, window);

	prime_SetClearColor(context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));

	prime_MakeActive(context);
	prime_SetVsync(context, true);

	while (!prime_WindowShouldClose(window)) {
		prime_PollEvents();

		prime_Clear(context);
		prime_Swapbuffers(context);
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
	prime_Window* dx11_window = prime_CreateWindow("Begin Multi Context Test Dx11", 640, 480);
	prime_Device* dx11_device = prime_CreateDevice(prime_DeviceTypeDx11);
	prime_Context* dx11_context = prime_CreateContext(dx11_device, dx11_window);

	prime_SetClearColor(dx11_context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_MakeActive(dx11_context);
	prime_SetVsync(dx11_context, true);

	// gl
	prime_Window* gl_window = prime_CreateWindow("Begin Multi Context Test GL", 640, 480);
	prime_Device* gl_device = prime_CreateDevice(prime_DeviceTypeGL);
	prime_Context* gl_context = prime_CreateContext(gl_device, gl_window);

	prime_SetClearColor(gl_context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_MakeActive(gl_context);
	prime_SetVsync(gl_context, true);

	while (!prime_WindowShouldClose(dx11_window)) {
		prime_PollEvents();

		// dx11
		prime_Clear(dx11_context);
		prime_Swapbuffers(dx11_context);

		// gl
		prime_Clear(gl_context);
		prime_Swapbuffers(gl_context);
	}

	// dx11
	prime_DestroyDevice(dx11_device);
	prime_DestroyWindow(dx11_window);

	// gl
	prime_DestroyDevice(gl_device);
	prime_DestroyWindow(gl_window);

	prime_LogInfo("End Multi Context Test");
	prime_LogInfo("");
	return PRIME_PASSED;
}