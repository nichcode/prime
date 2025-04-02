
#include "prime/prime.h"

int main() 
{
    prime_init(PRIME_DEVICE_OPENGL);

    PRIME_TRACE("hello from strings %f", 10.0f);
    PRIME_INFO("hello from strings %f", 10.0f);
    PRIME_WARN("hello from strings %f", 10.0f);
    PRIME_ERROR("hello from strings %f", 10.0f);

    prime_window_desc desc;
    desc.flag = PRIME_WINDOW_SHOW | PRIME_WINDOW_CENTER;
    desc.title = "prime window";
    desc.size = { 640, 480 };
    prime_window* window = prime_create_window(desc);

    while (!prime_window_should_close(window)) {
        prime_pull_events();
    }
    
    prime_destroy_window(window);
    prime_shutdown();
    return 0;
}