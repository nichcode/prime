
#include "prime/prime.h"

b8
windowTest();

b8
multiWindowTest();

b8
contextTestGL();

b8
buffersTestGL();

b8
mathTest();

b8
renderer2dTest();

#include "window_test.cpp"
#include "context_test.cpp"
#include "buffers_test.cpp"
#include "math_test.cpp"
#include "renderer2d_test.cpp"

int
main()
{
    using namespace prime;

    Platform::init();
    //TestManager::add("mathTest", mathTest);
    //TestManager::add("windowTest", windowTest);
    //TestManager::add("multiWindowTest", multiWindowTest);
    //TestManager::add("contextTestGL", contextTestGL);
    //TestManager::add("buffersTestGL", buffersTestGL);
    TestManager::add("renderer2dTest", renderer2dTest);

    TestManager::run();
    Platform::shutdown();
    return 0;
}