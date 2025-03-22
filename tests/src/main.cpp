
#include "prime/prime.h"

#include <iostream>

int main(int argc, char** argv)
{
    prime_device_type device_type;
    device_type = PRIME_DEVICE_TYPE_OPENGL;
    prime_init(device_type);

    prime_shutdown();
    return 0;
}