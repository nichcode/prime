
#include "prime/prime.h"

b8 contextTest(void* user_data)
{
    prime_window_desc desc;
    desc.size.x = 640;
    desc.size.y = 480;
    desc.title = "window";
    desc.flag = PRIME_WINDOW_FLAGS_CENTER;
    prime_window* window = prime_create_window(desc);

    prime_context* context = prime_create_context(window);
    prime_context_set_vsync(context, true);
    prime_context_set_clearcolori(context, { 50, 50, 50, 255 });

    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

    u32 indices[] = {0, 1, 2 };

    prime_buffer_desc buffer_desc;
    buffer_desc.data = nullptr;
    buffer_desc.size = 12;
    buffer_desc.type = PRIME_BUFFER_TYPE_VERTEX;
    buffer_desc.usage = PRIME_BUFFER_USAGE_DYNAMIC;

    prime_buffer* buffer = prime_create_buffer(context, buffer_desc);
    prime_buffer* buffer2 = prime_create_buffer(context, buffer_desc);
    prime_buffer* buffer3 = prime_create_buffer(context, buffer_desc);
    prime_buffer* buffer4 = prime_create_buffer(context, buffer_desc);
    prime_buffer* buffer5 = prime_create_buffer(context, buffer_desc);

    while (!prime_window_should_close(window)) {
        prime_pull_events();

        prime_context_clear(context);
        prime_context_present(context);
    }

    prime_destroy_context(context);
    prime_destroy_window(window);
    return PRIME_PASSED;
}