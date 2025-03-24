
#pragma once

#include "prime/defines.h"
#include "prime/maths.h"
#include "prime/input.h"

struct prime_window;

using prime_window_flag = u32;
using prime_window_close_func = void(*)(prime_window* window);
using prime_window_key_func = void(*)(prime_window* window, u32 key, i32 scancode, u8 action);
using prime_window_button_func = void(*)(prime_window* window, u16 button, u8 action);
using prime_window_mouse_moved_func = void(*)(prime_window* window, i32 x, i32 y);
using prime_window_mouse_scrolled_func = void(*)(prime_window* window, f32 x_offset, f32 y_offset);
using prime_window_moved_func = void(*)(prime_window* window, i32 x, i32 y);
using prime_window_resized_func = void(*)(prime_window* window, u32 width, u32 height);
using prime_window_focused_func = void(*)(prime_window* window, b8 focused);

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

PRIME_API void prime_pull_events();
PRIME_API void prime_hide_window(prime_window* window);
PRIME_API void prime_show_window(prime_window* window);
PRIME_API void prime_reset_callbacks();

PRIME_API void prime_set_window_pos(prime_window* window, prime_ivec2 pos);
PRIME_API void prime_set_window_size(prime_window* window, prime_uvec2 size);
PRIME_API void prime_set_window_title(prime_window* window, const char* title);

PRIME_API void prime_set_window_close_func(prime_window_close_func func);
PRIME_API void prime_set_window_key_func(prime_window_key_func func);
PRIME_API void prime_set_window_button_func(prime_window_button_func func);
PRIME_API void prime_set_window_mouse_moved_func(prime_window_mouse_moved_func func);
PRIME_API void prime_set_window_mouse_scrolled_func(prime_window_mouse_scrolled_func func);
PRIME_API void prime_set_window_moved_func(prime_window_moved_func func);
PRIME_API void prime_set_window_resized_func(prime_window_resized_func func);
PRIME_API void prime_set_window_focused_func(prime_window_focused_func func);

PRIME_API b8 prime_window_should_close(prime_window* window);
PRIME_API const void* prime_get_window_handle(prime_window* window);
PRIME_API const prime_ivec2* prime_get_window_pos(prime_window* window);
PRIME_API const prime_uvec2* prime_get_window_size(prime_window* window);
PRIME_API const char* prime_get_window_title(prime_window* window);

PRIME_API b8 prime_get_window_key(prime_window* window, prime_key key);
PRIME_API b8 prime_get_window_button(prime_window* window, prime_button button);
