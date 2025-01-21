
#include "prime/prime.h"

b8
renderer2DTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Renderer2D Test GL");

	prime_Device* device = prime_DeviceCreate(prime_DeviceTypeGL);
	prime_Window* window = prime_WindowCreate("Renderer2D Test GL", 640, 480);
	prime_Renderer2D* renderer = prime_Renderer2DCreate(device, window);
	prime_Renderer2DSetClearColor(renderer, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));

	while (!prime_WindowShouldClose(window)) {
		prime_WindowPollEvents();

		prime_Renderer2DClear(renderer);
		prime_Renderer2DBegin(renderer);

		prime_Renderer2DEnd(renderer);
		prime_Renderer2DPresent(renderer);
	}

	prime_Renderer2DDestroy(renderer);
	prime_DeviceDestroy(device);
	prime_WindowDestroy(window);

	prime_LogInfo("End Renderer2D Test GL");
	prime_LogInfo("");

	return PRIME_PASSED;
}