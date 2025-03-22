
#include "prime/prime.h"

int main(int argc, char** argv)
{
    prime_device_type device_type;
    device_type = PRIME_DEVICE_TYPE_OPENGL;
    prime_init(device_type);

    PRIME_TRACE("hello %f", 10.0f);
    PRIME_INFO("hello %f", 10.0f);
    PRIME_WARN("hello %f", 10.0f);
    PRIME_ERROR("hello %f", 10.0f);

    prime_shutdown();
    return 0;
}