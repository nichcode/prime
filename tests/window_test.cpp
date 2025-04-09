
#include "prime/prime.h"

int main(int argc, char** argv)
{
    b8 succes = prInit();
    PR_TRACE("hello %f", 20.0f);
    PR_INFO("hello %f", 20.0f);
    PR_WARN("hello %f", 20.0f);
    PR_ERROR("hello %f", 20.0f);

    prShutdown();
    return 0;
}