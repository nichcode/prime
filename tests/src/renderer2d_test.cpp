
#include "prime/prime.h"

b8 renderer2dTest(void* data)
{
    primeWindowDesc desc;
    desc.size.x = 640;
    desc.size.y = 480;
    desc.title = "window";
    desc.flag = primeWindowFlags_Center;
    primeWindow* window = primeCreateWindow(desc);

    primeContext* context = primeCreateContext(window);
    primeSetVsync(context, true);
    primeSetClearColori(context, { 50, 50, 50, 255 });

    primeRenderer2D* renderer = primeCreateRenderer2D(context);
    primeRenderer2DSetDrawColor(renderer, { 1.0f, 0.0, 0.0, 1.0f });
    primeRenderer2DSetTextColor(renderer, { 0.0f, 1.0f, 0.0f, 1.0f });

    primeTexture* texture = primeLoadTexture("textures/texture2d.png");
    primeFont* font = primeLoadFont("fonts/font.ttf", 30);
    primeFont* font2 = primeLoadFont("fonts/font2.ttf", 30);

    primeRenderer2DSetFontScale(renderer, 1.0f);

    primeRenderer2DSetTexture(renderer, texture);

    while (!primeWindowShouldClose(window)) {
        primePullEvents();

        primeClear(context);
        primeRenderer2DSetTexture(renderer, texture);

        primeRenderer2DDrawRect(renderer, { 0.0f, 0.0f, 50.0f, 50.0f });
        primeRenderer2DDrawTexture(renderer, { 100.0f, 200.0f });
        primeRenderer2DSetFont(renderer, font);
        primeRenderer2DDrawText(renderer, "Text Rendering", { 200.0f, 0.0f });
        primeRenderer2DDrawText(renderer, "Hello", { 200.0f, 50.0f });
        primeRenderer2DSetFont(renderer, font2);
        primeRenderer2DDrawText(renderer, "Text Rendering", { 200.0f, 100.0f });

        primeRenderer2DFlush(renderer);
        primePresent(context);
    }

    primeDestroyRenderer2D(renderer);
    primeDestroyContext(context);
    primeDestroyWindow(window);
    return PRIME_PASSED;
}