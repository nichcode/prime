
#include "prime/prime.h"

int main() 
{
    prime_Init(PRIME_DEVICE_OPENGL);

    PRIME_TRACE("hello from strings %f", 10.0f);
    PRIME_INFO("hello from strings %f", 10.0f);
    PRIME_WARN("hello from strings %f", 10.0f);
    PRIME_ERROR("hello from strings %f", 10.0f);

    prime_Shutdown();
    return 0;
}