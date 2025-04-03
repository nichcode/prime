
#include "prime/prime.h"

b8 contextTest()
{
    prime_window_desc desc;
    desc.flag = PRIME_WINDOW_SHOW | PRIME_WINDOW_CENTER;
    desc.title = "prime window";
    desc.size = { 640, 480 };
    prime_window* window = prime_create_window(desc);

    prime_context* context = prime_create_context(window);
    prime_make_active(context);
    prime_set_clear_color({ .2f, .2f, .2f, 1.0f });

    while (!prime_window_should_close(window)) {
        prime_pull_events();

        prime_clear();
        prime_swap_buffers();
    }

    prime_destroy_context(context);
    prime_destroy_window(window);
    return PRIME_PASSED;
}