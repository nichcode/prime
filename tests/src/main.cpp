
#include "prime/prime.h"

b8 mathsTest();
b8 windowTest();
b8 multiWindowTest();
b8 rendererAPITestGL();
b8 renderer2dTest();
b8 collisionTest();
b8 scene2dTest();
b8 physics2dTest();
b8 physics2dSceneTest();

int main()
{
    using namespace prime;

    core::Platform::init();

    //core::TestManager::addTest(mathsTest, "mathsTest");
    //core::TestManager::addTest(windowTest, "windowTest");
    //core::TestManager::addTest(multiWindowTest, "multiWindowTest");
    //core::TestManager::addTest(rendererAPITestGL, "rendererAPITestGL");
    //core::TestManager::addTest(renderer2dTest, "renderer2dTest");
    //core::TestManager::addTest(collisionTest, "collisionTest");
    //core::TestManager::addTest(scene2dTest, "scene2dTest");
    //core::TestManager::addTest(physics2dTest, "physics2dTest");
    core::TestManager::addTest(physics2dSceneTest, "physics2dSceneTest");

    core::TestManager::run();
    core::Platform::shutdown();
    return 0;
}