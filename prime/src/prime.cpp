
#include "prime/prime.h"
#include "pch.h"

// TODO: remove
#include <iostream>

struct prime_init_data
{
    prime_device_type type;
};

static prime_init_data s_init_data;

b8 prime_init(prime_device_type type)
{
    s_init_data.type = type;
    std::cout << "prime init" << std::endl;
    return PRIME_PASSED;
}

void prime_shutdown()
{
    std::cout << "prime shutdown" << std::endl;
}