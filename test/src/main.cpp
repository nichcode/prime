
#include "prime/prime.h"

b8
windowTest();

b8
multiWindowTest();

b8
contextTestGL();

#include "window_test.cpp"
#include "context_test.cpp"

int
main()
{
    using namespace prime;

    Platform::init();
    //TestManager::add("windowTest", windowTest);
    //TestManager::add("multiWindowTest", multiWindowTest);
    TestManager::add("contextTestGL", contextTestGL);

    TestManager::run();
    Platform::shutdown();
    return 0;
}