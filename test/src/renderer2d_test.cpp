
#include "prime/prime.h"

b8
renderer2dTest()
{
    using namespace prime;

    Window window;
    window.init("BuffersTestGL", 640, 480);

    prime::Ref<prime::Device> device;
    device = Platform::createDevice(DeviceType::OpenGL, window);

    device->setClearColor({ .2f, .2f, .2f, 1.0f });

    Renderer2D::init(device);

    while (!window.shouldClose()) {
        window.pollEvents();

        device->clear();

        Renderer2D::begin();

        Renderer2D::drawRect({  0.6f, 0.0f, 0.4f, 0.4f }, { 1.0f, 0.0f, 0.0f, 1.0f }, 1.0f);
        Renderer2D::drawRect({  0.5f, 0.0f, 0.4f, 0.4f }, 0.0f);

        Renderer2D::end();
        device->present();
    }

    Renderer2D::destroy();
    return PTRUE;
}