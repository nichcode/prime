
#include "pch.h"
#include "prime/platform.h"

b8 prInit()
{
    std::cout << "Init" << std::endl;
    return PR_PASSED;
}

void prShutdown()
{
    std::cout << "Shutdown" << std::endl;
}
