
#pragma once

#include "prime/defines.h"
#include "prime/maths.h"

struct prime_window;

using prime_window_flag = u32;
enum prime_window_flags
{
    NONE = 0,
    PRIME_WINDOW_FLAGS_CENTER = PRIME_BIT(0)
};

struct prime_window_desc
{
    prime_uvec2 size;
    prime_ivec2 pos;
    const char* title = nullptr;
    prime_window_flag flag;
};

PRIME_API prime_window* prime_create_window(prime_window_desc desc);
PRIME_API void prime_destroy_window(prime_window* window);

PRIME_API void prime_window_set_pos(prime_window* window, prime_ivec2 pos);
PRIME_API b8 prime_window_should_close(prime_window* window);

PRIME_API void prime_pull_events();

PRIME_API void* prime_get_window_handle(prime_window* window);
PRIME_API const prime_uvec2* prime_get_window_size(prime_window* window);