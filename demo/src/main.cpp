
#include "prime/prime.h"

#include <iostream>

int main() 
{
    prime_Init(PRIME_DEVICE_OPENGL);

    char* string = prime_Format("hello from strings %f", 10.0f);
    std::cout << string << std::endl;

    prime_Shutdown();
    return 0;
}