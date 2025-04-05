
#include "prime/prime.h"

#include "tests.h"

// src files
#include "tests.cpp"
#include "window_test.cpp"
#include "context_test.cpp"
#include "render_test.cpp"

int main() 
{
    prime_init(PRIME_DEVICE_OPENGL, true);

    //addTest(windowTest, "windowTest");
    //addTest(contextTest, "contextTest");
    addTest(renderTest, "renderTest");
    
    runTests();
    prime_shutdown();
    return 0;
}