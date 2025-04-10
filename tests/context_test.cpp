
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

    prBufferDesc buffer_desc;
    buffer_desc.type = prBufferTypes_Vertex;
    buffer_desc.data = nullptr;
    buffer_desc.size = 8;
    prBuffer* buffer = prCreateBuffer(context, buffer_desc);

    prBindBuffer(buffer);

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