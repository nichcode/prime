
#include "prime/prime.h"

b8 windowTest()
{
    prime_window_desc desc;
    desc.flag = PRIME_WINDOW_SHOW | PRIME_WINDOW_CENTER;
    desc.title = "prime window";
    desc.size = { 640, 480 };
    prime_window* window = prime_create_window(desc);

    while (!prime_window_should_close(window)) {
        prime_pull_events();

        prime_swap_buffers(window);
    }
    
    prime_destroy_window(window);
    return PRIME_PASSED;
}