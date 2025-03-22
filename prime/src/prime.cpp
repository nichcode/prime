
#include "prime/prime.h"
#include "pch.h"

struct prime_init_data
{
    prime_device_type type;
};

static prime_init_data s_init_data;

b8 prime_init(prime_device_type type)
{
    s_init_data.type = type;
    PRIME_INFO("prime init");
    return PRIME_PASSED;
}

void prime_shutdown()
{
    PRIME_INFO("prime shutdown");
}