
#include "prime/prime.h"

void onResize(prime_window* window, u32 width, u32 height)
{
    prime_context* context = (prime_context*)prime_get_user_data();
    prime_view view;
    view.width = (f32)width;
    view.height = (f32)height;
    prime_set_view(view);
}

b8 contextTest()
{
    prime_window_desc desc;
    desc.flag = PRIME_WINDOW_SHOW | PRIME_WINDOW_CENTER;
    prime_window* window = prime_create_window(desc);

    prime_context* context = prime_create_context(window);
    prime_make_active(context);
    prime_set_clear_color({ .2f, .2f, .2f, 1.0f });

    // draw a triangle
    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
	};

    u32 indices[] = { 0, 1, 2 };

    prime_layout layout;

    prime_attrib pos_attrib;
    pos_attrib.divisor = 0;
    pos_attrib.normalize = false;
    pos_attrib.type = PRIME_FLOAT3;

    prime_attrib color_attrib;
    color_attrib.divisor = 0;
    color_attrib.normalize = false;
    color_attrib.type = PRIME_FLOAT4;

    layout.attribs[0] = pos_attrib;
    layout.attribs[1] = color_attrib;
    layout.count = 2;

    prime_buffer_desc buffer_desc;
    buffer_desc.binding = 0;
    buffer_desc.data = vertices;
    buffer_desc.size = sizeof(vertices);
    buffer_desc.type = PRIME_BUFFER_VERTEX;
    buffer_desc.usage = PRIME_BUFFER_USAGE_STATIC;
    prime_buffer* vertex_buffer = prime_create_buffer(buffer_desc);

    buffer_desc.binding = 0;
    buffer_desc.data = indices;
    buffer_desc.size = sizeof(indices);
    buffer_desc.type = PRIME_BUFFER_INDEX;
    buffer_desc.usage = PRIME_BUFFER_USAGE_STATIC;
    prime_buffer* index_buffer = prime_create_buffer(buffer_desc);

    prime_shader_desc shader_desc;
    shader_desc.load = true;
    shader_desc.vertex_src = "shaders/vertex.glsl";
    shader_desc.pixel_src = "shaders/pixel.glsl";
    shader_desc.type = PRIME_GLSL;
    prime_shader* shader = prime_create_shader(shader_desc);

    prime_bind_buffer(vertex_buffer);
    prime_bind_buffer(index_buffer);
    prime_submit_layout(&layout);
    prime_bind_shader(shader);

    prime_set_window_resized_callback(onResize);
    prime_set_user_data(context);

    while (!prime_window_should_close(window)) {
        prime_pull_events();

        prime_clear();
        prime_submit_elements(PRIME_TRIANGLES, 3);
        prime_swap_buffers();
    }

    prime_destroy_shader(shader);
    prime_destroy_buffer(vertex_buffer);
    prime_destroy_buffer(index_buffer);
    prime_destroy_context(context);
    prime_destroy_window(window);
    return PRIME_PASSED;
}