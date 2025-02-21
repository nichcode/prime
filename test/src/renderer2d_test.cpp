
#include "prime/prime.h"

b8
renderer2dTestGL()
{
    primeDevice* device = primeDeviceCreate(primeDeviceTypeGL);
	primeWindow* window = primeWindowCreate("Renderer2D Test GL", 1000, 600);
	primeRenderer2D* renderer = primeRenderer2DCreate(device, window);

    primeColor clear_color = primeColorFromF32(.2f, .2f, .2f, 1.0f);
    primeColor draw_color = primeColorFromF32(0.0f, 0.0f, 1.0f, 1.0f);

	primeRenderer2DSetClearColor(renderer, &clear_color);

    primeTexture2D* texture = primeTexture2DLoad(device, "textures/tex2d.png");
	f32 rotation = 0.0f;

	while (!primeWindowShouldClose(window)) {
		primeWindowPollEvents();

		rotation += .3f;

		primeRenderer2DClear(renderer);
		primeRenderer2DBegin(renderer);

		const primeRect* view = primeRenderer2DGetView(renderer);

        primeRect rect;
        primeRect rect2;
		primeRect sprite;
		primeRect sprite2;
		rect2.x =  primeRectGetCenterX(view) - primeRectGetCenterX(&rect2);
		rect2.y =  primeRectGetCenterY(view) - primeRectGetCenterY(&rect2);

        primeRenderer2DDrawRect(renderer, &rect, PCOLOR_BLUE);
        primeRenderer2DDrawRectEx(renderer, &rect2, PCOLOR_BLUE, rotation, primeAnchorCenter);

		sprite.x = 600.0f;
		sprite.y = 200.0f;
		sprite.width = 200.0f;
		sprite.height = 200.0f;
		primeRenderer2DDrawSprite(renderer, &sprite, texture);

		sprite2.x =  primeRectGetCenterX(view) - primeRectGetCenterX(&sprite2);
		sprite2.y = 400.0f;
		sprite2.width = 100.0f;
		sprite2.height = 100.0f;
		primeRenderer2DDrawSpriteEx(
			renderer,
			&sprite2,
			texture,
			primeFlipNone,
			rotation,
			primeAnchorCenter,
			PCOLOR_WHITE
		);

        primeRenderer2DEnd(renderer);
		primeRenderer2DPresent(renderer);
	}

	primeRenderer2DDestroy(renderer);
	primeDeviceDestroy(device);
	primeWindowDestroy(window);

	return true;
}