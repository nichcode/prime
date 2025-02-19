
#include "prime/prime.h"

b8
renderer2dTestGL()
{
    primeDevice* device = primeDeviceCreate(primeDeviceTypeGL);
	primeWindow* window = primeWindowCreate("Renderer2D Test GL", 640, 480);
	primeRenderer2D* renderer = primeRenderer2DCreate(device, window);

    primeColor clear_color = primeColorFromF32(.2f, .2f, .2f, 1.0f);
    primeColor draw_color = primeColorFromF32(0.0f, 0.0f, 1.0f, 1.0f);

	primeRenderer2DSetClearColor(renderer, &clear_color);
	primeRenderer2DSetDrawColor(renderer, &draw_color);

	while (!primeWindowShouldClose(window)) {
		primeWindowPollEvents();

		primeRenderer2DClear(renderer);
		primeRenderer2DBegin(renderer);

        primeRect rect;
        primeRect rect2;
		rect2.x = 300.0f;
        primeRenderer2DDrawRect(renderer, &rect2);
        primeRenderer2DDrawRect(renderer, &rect);

        primeRenderer2DEnd(renderer);
		primeRenderer2DPresent(renderer);
	}

	primeRenderer2DDestroy(renderer);
	primeDeviceDestroy(device);
	primeWindowDestroy(window);

	return true;
}