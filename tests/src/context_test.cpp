
#include "prime/prime.h"

b8 contextTestGL()
{
    using namespace prime;
    using namespace prime::core;
    using namespace prime::renderer;

    Window window;
    window.init("ContextTestGL", 640, 480);

    Scope<Context> context = Context::create(GraphicsAPIGL, window);
    context->setVsync(true);
    context->setClearColor({ .2f, .2f, .2f, 1.0f });

    while (!window.shouldClose()) {
        window.pollEvents();

        context->clear();

        context->present();
    }

    return PRIME_TRUE;
}