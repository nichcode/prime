
#include "prime/prime.h"

using namespace prime;
using namespace prime::core;
using namespace prime::renderer;
using namespace prime::maths;
using namespace prime::scene;

b8 scene2dTest()
{
    Scope<Window> window = Platform::createWindow("Renderer2DTest", 640, 480);
    Scope<RendererAPI> rendererAPI = Platform::createAPI(GraphicsAPIGL, window);
    rendererAPI->setClearColor({ .2f, .2f, .2f, 1.0f });
    rendererAPI->setVsync(true);

    Renderer2D renderer;
    renderer.init(rendererAPI);
    renderer.setDrawColor(PRIME_COLOR_GREEN);

    Ref<Scene2D> scene = SceneManager::createScene2D();
    Entity entity = scene->createEntity();
    entity.addComponent<SpriteRenderer>().color = PRIME_COLOR_BLUE;

    Transform& transform = entity.getComponent<Transform>();
    transform.position.x = 400.0f;
    transform.position.y = 300.0f;
    transform.scale.x = 2.0f;
    transform.scale.y = 2.0f;

    while (!window->shouldClose()) {
        Window::pollEvents();

        rendererAPI->clear();

        scene->render(renderer);
        renderer.flush();
        rendererAPI->present();
    }

    return PRIME_TRUE;
}