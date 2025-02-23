
#include "prime/prime.h"

b8
contextTestGL()
{
    prime::Window window;
    window.init("WindowTest", 640, 480);

    prime::Device device;
    device.init(prime::DeviceType::OpenGL);

    prime::Context* context = device.createContext(window);
    context->setClearColor({ .2f, .2f, .2f, 1.0f });

    while (!window.shouldClose()) {
        window.pollEvents();

        context->clear();

        context->swapbuffers();
    }

    return PTRUE;
}