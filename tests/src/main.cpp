
#include "prime/prime.h"

b8 windowTest(void* data);
b8 contextTest(void* data);
b8 renderer2dTest(void* data);

int main(int argc, char** argv)
{
    primeDeviceType device_type;
    device_type = primeDeviceTypes_OpenGL;
    primeInit(device_type);

    primeSetTestsData(nullptr);
    //primeAddTest(windowTest, "windowTest");
    //primeAddTest(contextTest, "contextTest");
    primeAddTest(renderer2dTest, "renderer2dTest");

    primeRunTests();
    primeShutdown();
    
    return 0;
}