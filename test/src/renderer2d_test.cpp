
#include "prime/prime.h"

static void
onWindowResize(prime_Window* window, u32 width, u32 height)
{
	prime_Renderer2D* ren = (prime_Renderer2D*)prime_WindowGetUserData(window);
	prime_Viewport viewport;
	viewport.width = width;
	viewport.height = height;
	prime_Renderer2DSetViewport(ren, viewport);

	/*if (prime_WindowMaximized(window)) {
		prime_Renderer2DSetScale(ren, { 2.0f, 2.0f });
	}
	else {
		prime_Renderer2DSetScale(ren, { 1.0f, 1.0f });
	}*/
}

b8
renderer2DTestGL()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Renderer2D Test GL");

	prime_Device* device = prime_DeviceCreate(prime_DeviceTypeGL);
	prime_Window* window = prime_WindowCreate("Renderer2D Test GL", 640, 480);
	prime_Renderer2D* renderer = prime_Renderer2DCreate(device, window);
	prime_Renderer2DSetClearColor(renderer, prime_ColorFromF32(.2f, .2f, .2f, 1.0f));

	prime_Renderer2DSetDrawColor(renderer, prime_ColorFromF32(0.0f, 0.0f, 1.0f, 1.0f));

	prime_Texture2D* texture = prime_Texture2DLoad(device, "textures/texture2d.png");

	f32 rotation = 0.0f;
	prime_WindowSetUserData(window, renderer);

	prime_WindowSetSizeCallback(onWindowResize);

	while (!prime_WindowShouldClose(window)) {
		prime_WindowPollEvents();

		rotation += .08f;

		prime_Renderer2DClear(renderer);
		prime_Renderer2DBegin(renderer);

		prime_Rect2D rect;
		rect.x = prime_WindowGetWidth(window) - rect.width;
		rect.y = 0.0f;

		// sprites
		prime_Renderer2DDrawRect(renderer, rect);
		prime_Renderer2DDrawRectEx(renderer, prime_Rect2DCreate(10.0f, 20.0f, 50.0f, 50.0f), rotation, prime_AnchorCenter);
		prime_Renderer2DDrawSprite(renderer, prime_Rect2DCreate(300.0f, 300.0f, 100.0f, 100.0f), texture);
		prime_Renderer2DDrawSpriteEx(renderer, prime_Rect2DCreate(300.0f, 50.0f, 50.0f, 50.0f), texture, rotation, prime_AnchorTopLeft, true, true);

		// lines
		prime_Renderer2DDrawLine(renderer, prime_Vec2Create(100.0f, 50.0f), prime_Vec2Create(200.0f, 50.0f));

		// rects
		prime_Renderer2DDrawRect(renderer, prime_Rect2DCreate(10.0f, 100.0f, 50.0f, 50.0f), false);
		prime_Renderer2DDrawRectEx(renderer, prime_Rect2DCreate(10.0f, 200.0f, 50.0f, 50.0f), rotation, prime_AnchorCenter, false);

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