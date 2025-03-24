
#pragma once

#include "defines.h"

using prime_test_func = b8(*)(void* user_data);

PRIME_API void prime_set_tests_data(void* user_data);

PRIME_API i32 prime_add_test(prime_test_func func, const char* name);
PRIME_API void prime_run_tests();