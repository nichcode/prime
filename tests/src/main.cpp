
#include "prime/prime.h"

b8 vec2Test();
b8 vec3Test();

int main()
{
    using namespace prime::core;

    Platform::init();

    //TestManager::addTest(vec2Test, "vec2Test");
    TestManager::addTest(vec3Test, "vec3Test");

    TestManager::run();
    Platform::shutdown();
    return 0;
}