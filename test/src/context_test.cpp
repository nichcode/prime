
#include "prime/prime.h"

b8
contextTestGL()
{
    prime::Window window;
    window.init("ContestTestGL", 640, 480);

    prime::Ref<prime::Device> device;
    device = prime::Platform::createDevice(prime::DeviceType::OpenGL, window);
    device->setClearColor({ .2f, .2f, .2f, 1.0f });

    while (!window.shouldClose()) {
        window.pollEvents();

        device->clear();

        device->present();
    }

    return PTRUE;
}