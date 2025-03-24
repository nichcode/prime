
#pragma once

#include "defines.h"

PRIME_API void* prime_load_library(const char* dll);
PRIME_API void* prime_load_library_func(void* dll, const char* func_name);
PRIME_API void prime_free_library(void* dll);