
#include "prime/prime.h"

int 
main(int argc, char** argv)
{
    u8 success = prime_PlatformInit();
    if (success) {

        prime_RunTests();
        prime_PlatformShutdown();
        return 0;
    }
    return -1;
}