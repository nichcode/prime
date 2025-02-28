
#include "prime/prime.h"

#define USE_NDC

b8
renderer2dTest()
{
    using namespace prime;

    Window window;
    window.init("BuffersTestGL", 640, 480);

    Ref<Device> device = Platform::createDevice(DeviceType::OpenGL, window);

    Ref<Texture> texture = device->createTexture("textures/texture2d.png");

    Renderer2D renderer;
#ifdef USE_NDC
    renderer.init(device, true);
#else 
    renderer.init(device);
#endif // USE_NDC

    device->setClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });

    while (!window.shouldClose()) {
        window.pollEvents();

        device->clear();
        renderer.begin();

        renderer.setLayer(prime::Layer::One);

#ifdef USE_NDC
        renderer.drawRect({  -0.4f, 0.0f, 0.4f, 0.4f }, { 1.0f, 0.0f, 0.0f, 1.0f });
        renderer.drawSprite({ 0.4f, 0.0f, 1.0f, 1.0f }, texture);

#else
        renderer.drawRect({  0.0f, 0.0f, 50.0f, 50.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
        renderer.drawSprite({ 200.0f, 100.0f, 100.0f, 100.0f }, texture);

#endif // USE_NDC

        renderer.end();
        device->present();
    }

    renderer.destroy();
    return PTRUE;
}