
#include "prime/prime_platform.h"

int 
main(int argc, char** argv)
{
    u8 success = prime_PlatformInit();
    if (success) {
        prime_PlatformShutdown();
        return 0;
    }
    return -1;
}