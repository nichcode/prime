
#include "prime/prime.h"

#include "tests.h"

// src files
#include "tests.cpp"
#include "window_test.cpp"

int main() 
{
    prime_init(PRIME_DEVICE_OPENGL);

    addTest(windowTest);
    runTests();

    prime_shutdown();
    return 0;
}