
#include "prime/prime.h"

b8 vec2Test();

int main()
{
    using namespace prime::core;

    Platform::init();

    TestManager::addTest(vec2Test, "vec2Test");

    TestManager::run();
    Platform::shutdown();
    return 0;
}