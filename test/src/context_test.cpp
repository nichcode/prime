
#include "tests.h"

b8
contextTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Context Test GL");

	prime_Device* device = prime_DeviceCreate(prime_DeviceTypeGL);
	prime_Window* window = prime_WindowCreate("Begin Context Test GL", 640, 480);
	prime_Context* context = prime_ContextCreate(device, window);

	prime_ContextMakeActive(context);
	prime_ContextSetClearColor(context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_ContextSetVsync(context, true);

	while (!prime_WindowShouldClose(window)) {
		prime_WindowPollEvents();

		prime_ContextClear(context);
		prime_ContextSwapbuffers(context);
	}

	prime_DeviceDestroy(device);
	prime_WindowDestroy(window);

	prime_LogInfo("End Context Test GL");
	prime_LogInfo("");
	return PRIME_PASSED;
}

b8
contextTestDx11()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Context Test Dx11");

	prime_Window* window = prime_WindowCreate("Begin Context Test Dx11", 640, 480);
	prime_Device* device = prime_DeviceCreate(prime_DeviceTypeGL);
	prime_Context* context = prime_ContextCreate(device, window);

	prime_ContextSetClearColor(context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));

	prime_ContextMakeActive(context);
	prime_ContextSetVsync(context, true);

	while (!prime_WindowShouldClose(window)) {
		prime_WindowPollEvents();

		prime_ContextClear(context);
		prime_ContextSwapbuffers(context);
	}

	prime_DeviceDestroy(device);
	prime_WindowDestroy(window);

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
	prime_Window* dx11_window = prime_WindowCreate("Begin Multi Context Test Dx11", 640, 480);
	prime_Device* dx11_device = prime_DeviceCreate(prime_DeviceTypeDx11);
	prime_Context* dx11_context = prime_ContextCreate(dx11_device, dx11_window);

	prime_ContextSetClearColor(dx11_context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_ContextMakeActive(dx11_context);
	prime_ContextSetVsync(dx11_context, true);

	// gl
	prime_Window* gl_window = prime_WindowCreate("Begin Multi Context Test GL", 640, 480);
	prime_Device* gl_device = prime_DeviceCreate(prime_DeviceTypeGL);
	prime_Context* gl_context = prime_ContextCreate(gl_device, gl_window);

	prime_ContextSetClearColor(gl_context, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));
	prime_ContextMakeActive(gl_context);
	prime_ContextSetVsync(gl_context, true);

	while (!prime_WindowShouldClose(dx11_window)) {
		prime_WindowPollEvents();

		// dx11
		prime_ContextClear(dx11_context);
		prime_ContextSwapbuffers(dx11_context);

		// gl
		prime_ContextClear(gl_context);
		prime_ContextSwapbuffers(gl_context);
	}

	// dx11
	prime_DeviceDestroy(dx11_device);
	prime_WindowDestroy(dx11_window);

	// gl
	prime_DeviceDestroy(gl_device);
	prime_WindowDestroy(gl_window);

	prime_LogInfo("End Multi Context Test");
	prime_LogInfo("");
	return PRIME_PASSED;
}