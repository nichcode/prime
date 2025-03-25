
#include "prime/prime.h"

b8 renderer2dTest(void* data)
{
    primeWindowDesc desc;
    desc.size.x = 640;
    desc.size.y = 480;
    desc.title = "window";
    desc.flag = PRIME_WINDOW_FLAGS_CENTER;
    primeWindow* window = primeCreateWindow(desc);

    primeContext* context = primeCreateContext(window);
    primeSetVsync(context, true);
    primeSetClearColori(context, { 50, 50, 50, 255 });

    primeRenderer2D* renderer = primeCreateRenderer2D(context);
    primeSetDrawColor(renderer, { 1.0f, 0.0, 0.0, 1.0f });

    while (!primeWindowShouldClose(window)) {
        primePullEvents();

        primeClear(context);

        primeDrawRect(renderer, { 0.0f, 0.0f, 50.0f, 50.0f });
        primeDrawRect(renderer, { 100.0f, 200.0f, 50.0f, 50.0f });

        primeRenderer2DFlush(renderer);
        primePresent(context);
    }

    primeDestroyRenderer2D(renderer);
    primeDestroyContext(context);
    primeDestroyWindow(window);
    return PRIME_PASSED;
}