
#include "prime/prime.h"

void onWindowClose(prime_window* window)
{
	const char* title = prime_get_window_title(window);
    prime_log_info("%s is closed", title);
}

void onWindowResize(prime_window* window, u32 width, u32 height)
{
    const char* title = prime_get_window_title(window);
    prime_log_info("size(%i, %i)", width, height);
}

void onWindowKey(prime_window* window, u32 key, i32 scancode, u32 action)
{
    const char* title = prime_get_window_title(window);
    prime_log_info(
        "%s - %s, %s", title, 
        prime_get_key_name(key), 
        prime_get_action_name(action)
    );
}

void onWindowButton(prime_window* window, u32 button, u32 action)
{
    const char* title = prime_get_window_title(window);
    prime_log_info(
        "%s - %s, %s", title, 
        prime_get_button_name(button), 
        prime_get_action_name(action)
    );
}

void onWindowMouseMoved(prime_window* window, i32 x, i32 y)
{
    const char* title = prime_get_window_title(window);
	prime_log_info("%s - mousePos(%i, %i))", title, x, y);
}

void onWindowMouseScrolled(prime_window* window, f32 x_offset, f32 y_offset)
{
    const char* title = prime_get_window_title(window);
	prime_log_info("%s - mouseScroll(%i, %i))", title, x_offset, y_offset);
}

void onWindowMoved(prime_window* window, i32 x, i32 y)
{
    const char* title = prime_get_window_title(window);
	prime_log_info("%s - windowPos(%i, %i))", title, x, y);
}

void onWindowFocused(prime_window* window, b8 focused)
{
    if (focused) {
        const char* title = prime_get_window_title(window);
		prime_log_info("%s is focused", title);
	}
}

b8 windowTest()
{
    prime_window_desc desc;
    desc.flag = PRIME_WINDOW_SHOW | PRIME_WINDOW_CENTER;
    prime_window* window = prime_create_window(desc);

    prime_set_close_callback(onWindowClose);
    prime_set_key_callback(onWindowKey);
    prime_set_button_callback(onWindowButton);
    prime_set_mouse_moved_callback(onWindowMouseMoved);
    prime_set_mouse_scrolled_callback(onWindowMouseScrolled);
    prime_set_window_moved_callback(onWindowMoved);
    prime_set_window_resized_callback(onWindowResize);
    prime_set_window_focused_callback(onWindowFocused);

    while (!prime_window_should_close(window)) {
        prime_pull_events();
    }

    prime_reset_callbacks();
    prime_destroy_window(window);
    return PRIME_PASSED;
}