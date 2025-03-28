
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
    primeSetDrawColor(renderer, { 1.0f, 0.0, 0.0, 1.0f });
    primeSetTextColor(renderer, { 0.0f, 1.0f, 0.0f, 1.0f });

    primeTexture* texture = primeLoadTexture("textures/texture2d.png");
    primeFont* font = primeLoadFont("fonts/font.ttf", 30);
    primeFont* font2 = primeLoadFont("fonts/font2.ttf", 30);

    while (!primeWindowShouldClose(window)) {
        primePullEvents();

        primeClear(context);

        primeDrawRect(renderer, { 0.0f, 0.0f, 50.0f, 50.0f });
        primeDrawTexture(renderer, { 100.0f, 200.0f }, texture);
        primeSetFont(renderer, font);
        primeDrawText(renderer, "Text Rendering", { 200.0f, 00.0f });
        primeSetFont(renderer, font2);
        primeDrawText(renderer, "Text Rendering", { 200.0f, 100.0f });

        primeRenderer2DFlush(renderer);
        primePresent(context);
    }

    primeDestroyRenderer2D(renderer);
    primeDestroyContext(context);
    primeDestroyWindow(window);
    return PRIME_PASSED;
}