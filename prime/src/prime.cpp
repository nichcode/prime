
#include "prime/prime.h"
#include "pch.h"
#include "win32/wgl_context.h"
#include "utils.h"

b8 prime_init(prime_device_type type)
{
    s_init_data.type = type;
    switch (type)
    {
    case PRIME_DEVICE_TYPE_OPENGL:
        createDummyWGLContext();
        break;
    }
    PRIME_INFO("prime init");
    return PRIME_PASSED;
}

void prime_shutdown()
{
    PRIME_INFO("prime shutdown");
}