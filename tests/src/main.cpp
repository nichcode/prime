
#include "prime/prime.h"

b8 mathsTest();
b8 windowTest();
b8 multiWindowTest();
b8 rendererAPITestGL();

int main()
{
    using namespace prime;

    core::Platform::init();

    //core::TestManager::addTest(mathsTest, "mathsTest");
    //core::TestManager::addTest(windowTest, "windowTest");
    //core::TestManager::addTest(multiWindowTest, "multiWindowTest");
    core::TestManager::addTest(rendererAPITestGL, "rendererAPITestGL");

    core::TestManager::run();
    core::Platform::shutdown();
    return 0;
}