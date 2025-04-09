
#include "prime/prime.h"

int main(int argc, char** argv)
{
    b8 succes = prInit();

    u32 flags = prWindowFlags_Center | prWindowFlags_Show;
    prWindow* window = prCreateWindow("window", 640, 480, flags);

    while (!prWindowShouldClose(window)) {
        prPullEvents();
    }

    prDestroyWindow(window);
    prShutdown();
    return 0;
}