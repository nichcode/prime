
#include "pch.h"
#include "prime/pr_platform.h"
#include <iostream>

b8 prInit(prDeviceType type)
{
    std::cout << "Init" << std::endl;
    return PR_PASSED;
}

void prShutdown()
{
    std::cout << "Shutdown" << std::endl;
}