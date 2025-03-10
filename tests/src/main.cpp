
#include "prime/prime.h"

b8 mathsTest();

int main()
{
    using namespace prime;

    core::Platform::init();

    core::TestManager::addTest(mathsTest, "mathsTest");

    core::TestManager::run();
    core::Platform::shutdown();
    return 0;
}