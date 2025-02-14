
#include "prime/prime.h"

b8
stringTest();

b8
windowTest();

b8
multiWindowTest();

b8
contextTestGL();

#include "string_test.cpp"
#include "window_test.cpp"
#include "context_test.cpp"

#include <iostream>

int 
main(int argc, char** argv)
{
    u8 success = primePlatformInit();
    if (success) {

        //primeAddTest("stringTest", stringTest);
        //primeAddTest("windowTest", windowTest);
        //primeAddTest("multiWindowTest", multiWindowTest);
        primeAddTest("contextTestGL", contextTestGL);

        primeRunTests();
        primePlatformShutdown();
        
        system("pause");
        return 0;
    }
    system("pause");
    return -1;
}