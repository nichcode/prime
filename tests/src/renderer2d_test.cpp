
#include "prime/prime.h"

b8 renderer2dTest()
{
    using namespace prime::core;
    using namespace prime::renderer;

    Scope<Window> window = Platform::createWindow("Renderer2DTest", 640, 480);
    Scope<RendererAPI> rendererAPI = Platform::createAPI(prime::GraphicsAPIGL, window);
    rendererAPI->setClearColor({ .2f, .2f, .2f, 1.0f });
    rendererAPI->setVsync(true);

    Renderer2D renderer;
    renderer.init(rendererAPI.get());
    renderer.setDrawColor(PRIME_COLOR_GREEN);

    Camera2D camera;
    camera.setProjection(640, 480);

    Texture* texture = rendererAPI->loadTexture("textures/texture2d.png");
    f32 rotation = 0.0f;

    while (!window->shouldClose()) {
        Window::pollEvents();

        rendererAPI->clear();
        rotation += 2.0f;

        renderer.setCamera(camera);

        renderer.draw({ 0.0f, 0.0f });
        renderer.draw({ 200.0f, 200.0f }, { 100.0f, 100.0f }, texture, false, true);

        renderer.draw({ 100.0f, 200.0f }, { 50.0f, 50.0f }, rotation);
        renderer.draw({ 300.0f, 300.0f }, { 100.0f, 100.0f }, texture, 45.0f);

        renderer.flush();

        rendererAPI->present();
    }

    return PRIME_TRUE;
}