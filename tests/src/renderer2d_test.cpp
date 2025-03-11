
#include "prime/prime.h"

b8 renderer2dTest()
{
    using namespace prime::core;
    using namespace prime::renderer;

    Scope<Window> window = Platform::createWindow("RendererAPITestGL", 640, 480);
    Scope<RendererAPI> rendererAPI = Platform::createAPI(prime::GraphicsAPIGL, window);
    rendererAPI->setClearColor({ .2f, .2f, .2f, 1.0f });

    Renderer2D renderer;
    renderer.init(rendererAPI.get());
    renderer.setDrawColor(PRIME_COLOR_GREEN);

    Camera2D camera;
    camera.setProjection(640, 480);

    while (!window->shouldClose()) {
        Window::pollEvents();

        rendererAPI->clear();

        renderer.draw({ 0.0f, 0.0f });
        renderer.draw({ 200.0f, 200.0f }, { 100.0f, 100.0f });
        renderer.flush(camera);

        rendererAPI->present();
    }

    return PRIME_TRUE;
}