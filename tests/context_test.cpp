
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
    prMakeActive(context);
    prSetVsync(true);
    prSetClearColor(.2f, .2f, .2f, 1.0f);

    while (!prWindowShouldClose(window)) {
        prPullEvents();

        prClear();
        prSwapBuffers();
    }

    prDestroyContext(context);
    prDestroyWindow(window);
    prShutdown();
    return 0;
}