
#include "prime/prime.h"

b8 windowTest(void* data);
b8 contextTest(void* data);

int main(int argc, char** argv)
{
    primeDeviceType device_type;
    device_type = PRIME_DEVICE_TYPE_OPENGL;
    primeInit(device_type);

    primeSetTestsData(nullptr);
    //primeAddTest(windowTest, "windowTest");
    primeAddTest(contextTest, "contextTest");

    primeRunTests();
    primeShutdown();
    
    return 0;
}