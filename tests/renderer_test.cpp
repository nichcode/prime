
#include "prime/prime.h"

int main(int argc, char** argv)
{
    prInit();

    u32 flags = prWindowFlags_Center | prWindowFlags_Show;
    prWindow* window = prCreateWindow("window", 640, 480, flags);

    prContextDesc desc;
    desc.type = prContextTypes_OpenGL;
    desc.major = 3;
    desc.minor = 3;
    prContext* context = prCreateContext(window, desc);
    prMakeActive(context, false);
    prSetVsync(true);
    prSetClearColor(.2f, .2f, .2f, 1.0f);

    prRenderer* renderer = prCreateRenderer(context);
    prSetRendererDrawColor(renderer, 0.0f, 0.0f, 1.0f, 1.0f);

    prCamera camera;
    camera.aspect_ratio = 1.77f;
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;
   
    while (!prWindowShouldClose(window)) {
        prPullEvents();

        prClear();
        prSetRendererCamera(renderer, camera);

        prRendererDrawRect(renderer, { 0.0f, 0.0f, 0.5f, 0.5f });

        prRendererFlush(renderer);
        prSwapBuffers();
    }

    prDestroyRenderer(renderer);
    prDestroyContext(context);
    prDestroyWindow(window);
    prShutdown();
    return 0;
}