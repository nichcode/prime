
#include "prime/prime.h"

b8 renderTest()
{
    prime_window_desc desc;
    desc.flag = PRIME_WINDOW_SHOW | PRIME_WINDOW_CENTER;
    prime_window* window = prime_create_window(desc);

    prime_context* context = prime_create_context(window);
    prime_make_active(context);
    prime_set_clear_color({ .2f, .2f, .2f, 1.0f });

    prime_set_draw_color({ 0.0f, 1.0f, 0.0f, 1.0f });
    prime_draw_rect({ 0.0f, 0.0f, 1.0f, 1.0f });

    while (!prime_window_should_close(window)) {
        prime_pull_events();

        prime_clear();
        prime_flush();
        prime_swap_buffers();
    }

    return PRIME_TRUE;
}