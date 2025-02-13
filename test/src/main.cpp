
#include "prime/prime.h"

b8
stringTest();

#include "string_test.cpp"

#include <iostream>

int 
main(int argc, char** argv)
{
    u8 success = prime_PlatformInit();
    if (success) {

        prime_AddTest("stringTest", stringTest);

        prime_RunTests();
        prime_PlatformShutdown();
        
        system("pause");
        return 0;
    }
    system("pause");
    return -1;
}