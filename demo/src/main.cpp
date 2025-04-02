
#include "prime/prime.h"

int main() 
{
    prime_init(PRIME_DEVICE_OPENGL);

    PRIME_TRACE("hello from strings %f", 10.0f);
    PRIME_INFO("hello from strings %f", 10.0f);
    PRIME_WARN("hello from strings %f", 10.0f);
    PRIME_ERROR("hello from strings %f", 10.0f);

    prime_shutdown();
    return 0;
}