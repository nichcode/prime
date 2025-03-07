
#include "prime/prime.h"

b8 vec2Test();
b8 vec3Test();
b8 vec4Test();
b8 mat4Test();
b8 windowTest();
b8 multiWindowTest();
b8 contextTestGL();

int main()
{
    using namespace prime::core;

    Platform::init();

    //TestManager::addTest(vec2Test, "vec2Test");
    //TestManager::addTest(vec3Test, "vec3Test");
    //TestManager::addTest(vec4Test, "vec4Test");
    //TestManager::addTest(mat4Test, "mat4Test");
    //TestManager::addTest(windowTest, "windowTest");
    //TestManager::addTest(multiWindowTest, "multiWindowTest");
    TestManager::addTest(contextTestGL, "contextTestGL");

    TestManager::run();
    Platform::shutdown();
    return 0;
}