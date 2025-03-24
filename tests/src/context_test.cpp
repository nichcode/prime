
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

    u32 indices[] = {0, 1, 2, 2, 3, 0 };

    prime_layout* layout = prime_create_layout(context);
    prime_add_attrib(layout, PRIME_DATA_TYPE_FLOAT3, 0, false);

    prime_buffer_desc buffer_desc;
    buffer_desc.data = vertices;
    buffer_desc.size = sizeof(vertices);
    buffer_desc.type = PRIME_BUFFER_TYPE_VERTEX;
    buffer_desc.usage = PRIME_BUFFER_USAGE_STATIC;
    prime_buffer* vertex_buffer = prime_create_buffer(context, buffer_desc);

    buffer_desc.data = indices;
    buffer_desc.size = sizeof(indices);
    buffer_desc.type = PRIME_BUFFER_TYPE_INDEX;
    buffer_desc.usage = PRIME_BUFFER_USAGE_STATIC;
    prime_buffer* index_buffer = prime_create_buffer(context, buffer_desc);

    prime_set_layout(layout);

    prime_shader_desc shader_desc;
    shader_desc.load = true;
    shader_desc.vertex_src = "shaders/vertex.glsl";
    shader_desc.pixel_src = "shaders/pixel.glsl";
    shader_desc.source_type = PRIME_SHADER_SOURCE_TYPE_GLSL;
    prime_shader* shader = prime_create_shader(context, shader_desc);

    while (!prime_window_should_close(window)) {
        prime_pull_events();

        prime_context_clear(context);
        prime_set_shader(shader);
        prime_context_submit(context, PRIME_DRAW_TYPE_ELEMENTS, PRIME_DRAW_MODE_TRIANGLES, 6);
        prime_context_present(context);
    }

    prime_destroy_context(context);
    prime_destroy_window(window);
    return PRIME_PASSED;
}