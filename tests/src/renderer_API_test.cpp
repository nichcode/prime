
#include "prime/prime.h"

b8 rendererAPITestGL()
{
    using namespace prime::core;
    using namespace prime::renderer;

    Scope<Window> window = Platform::createWindow("WindowTest", 640, 480);
    Scope<RendererAPI> rendererAPI = Platform::createAPI(prime::GraphicsAPIGL, window);
    rendererAPI->setClearColor({ .2f, .2f, .2f, 1.0f });

    VertexArray* vertex_array = rendererAPI->createVertexArray();

    while (!window->shouldClose()) {
        Window::pollEvents();

        rendererAPI->clear();
        rendererAPI->present();
    }

    return PRIME_TRUE;
}
