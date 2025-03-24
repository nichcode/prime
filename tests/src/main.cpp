
#include "prime/prime.h"

int main(int argc, char** argv)
{
    prime_device_type device_type;
    device_type = PRIME_DEVICE_TYPE_OPENGL;
    prime_init(device_type);

    prime_window_desc desc;
    desc.size.x = 640;
    desc.size.y = 480;
    desc.title = "window";
    desc.flag = PRIME_WINDOW_FLAGS_CENTER;
    prime_window* window = prime_create_window(desc);

    prime_context* context = prime_create_context(window);
    prime_context_set_vsync(context, true);
    prime_context_set_clearcolori(context, { 50, 50, 50, 255 });

    while (!prime_window_should_close(window)) {
        prime_pull_events();

        prime_context_clear(context);
        prime_context_present(context);
    }

    prime_destroy_context(context);
    prime_destroy_window(window);
    prime_shutdown();
    
    return 0;
}