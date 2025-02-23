
#include "prime/prime.h"

b8
windowTest();

b8
multiWindowTest();

#include "window_test.cpp"

int
main()
{
    using namespace prime;

    Platform::init();
    TestManager::add("windowTest", windowTest);
    //TestManager::add("multiWindowTest", multiWindowTest);

    TestManager::run();
    Platform::shutdown();
    return 0;
}