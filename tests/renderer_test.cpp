
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

    prRenderer* renderer = prCreateRenderer(context, true);
   
    while (!prWindowShouldClose(window)) {
        prPullEvents();

        prDrawRect(renderer, { 0.0f, 0.0f, 0.5f, 0.5f });

        prClear();
        prFlush(renderer);
        prSwapBuffers();
    }

    prDestroyRenderer(renderer);
    prDestroyContext(context);
    prDestroyWindow(window);
    prShutdown();
    return 0;
}