
#pragma once

#include "prime_input.h"
#include "prime_maths.h"

struct prime_window;

using prime_close_func = void(*)(prime_window* window);
using prime_key_func = void(*)(prime_window* window, u32 key, i32 scancode, u32 action);
using prime_button_func = void(*)(prime_window* window, u32 button, u32 action);
using prime_mouse_moved_func = void(*)(prime_window* window, i32 x, i32 y);
using prime_mouse_scrolled_func = void(*)(prime_window* window, f32 offset_x, f32 offset_y);
using prime_window_moved_func = void(*)(prime_window* window, i32 x, i32 y);
using prime_window_resized_func = void(*)(prime_window* window, u32 width, u32 height);
using prime_window_focused_func = void(*)(prime_window* window, b8 focused);

enum prime_window_flags
{
    PRIME_WINDOW_SHOW = PRIME_BIT(0),
    PRIME_WINDOW_CENTER = PRIME_BIT(1)
};

struct prime_window_desc
{
    prime_vec2u size;
    prime_vec2i pos;
    const char* title = "prime window";
    u32 flag;
};

PRIME_API prime_window* prime_create_window(prime_window_desc desc);
PRIME_API void prime_destroy_window(prime_window* window);

PRIME_API void prime_pull_events();
PRIME_API void prime_hide_Window(prime_window* window);
PRIME_API void prime_show_window(prime_window* window);
PRIME_API void prime_reset_callbacks();

PRIME_API void prime_set_window_pos(prime_window* window, prime_vec2i pos);
PRIME_API void prime_set_window_size(prime_window* window, prime_vec2u size);
PRIME_API void prime_set_window_title(prime_window* window, const char* title);

PRIME_API void prime_set_close_callback(prime_close_func callback);
PRIME_API void prime_set_key_callback(prime_key_func callback);
PRIME_API void prime_set_button_callback(prime_button_func callback);
PRIME_API void prime_set_mouse_moved_callback(prime_mouse_moved_func callback);
PRIME_API void prime_set_mouse_scrolled_callback(prime_mouse_scrolled_func callback);
PRIME_API void prime_set_window_Moved_callback(prime_window_moved_func callback);
PRIME_API void prime_set_window_resized_callback(prime_window_resized_func callback);
PRIME_API void prime_set_window_focused_callback(prime_window_focused_func callback);

PRIME_API b8 prime_window_should_close(prime_window* window);
PRIME_API b8 prime_is_maximized(prime_window* window);

PRIME_API const void* prime_get_window_handle(prime_window* window);
PRIME_API prime_vec2i prime_get_window_pos(prime_window* window);
PRIME_API prime_vec2u prime_get_window_size(prime_window* window);
PRIME_API const char* prime_get_window_title(prime_window* window);