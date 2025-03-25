
#include "prime/prime.h"

b8 contextTest(void* data)
{
    primeWindowDesc desc;
    desc.size.x = 640;
    desc.size.y = 480;
    desc.title = "window";
    desc.flag = PRIME_WINDOW_FLAGS_CENTER;
    primeWindow* window = primeCreateWindow(desc);

    primeContext* context = primeCreateContext(window);
    primeSetVsync(context, true);
    primeSetClearColori(context, { 50, 50, 50, 255 });

    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

    u32 indices[] = {0, 1, 2, 2, 3, 0 };

    primeLayout* layout = primeCreateLayout(context);
    primeAddAttrib(layout, PRIME_DATA_TYPE_FLOAT3, 0, false);

    primeBufferDesc buffer_desc;
    buffer_desc.data = vertices;
    buffer_desc.size = sizeof(vertices);
    buffer_desc.type = PRIME_BUFFER_TYPE_VERTEX;
    buffer_desc.usage = PRIME_BUFFER_USAGE_STATIC;
    primeBuffer* vertex_buffer = primeCreateBuffer(context, buffer_desc);

    buffer_desc.data = indices;
    buffer_desc.size = sizeof(indices);
    buffer_desc.type = PRIME_BUFFER_TYPE_INDEX;
    buffer_desc.usage = PRIME_BUFFER_USAGE_STATIC;
    primeBuffer* index_buffer = primeCreateBuffer(context, buffer_desc);

    primeSetLayout(layout);

    primeShaderDesc shader_desc;
    shader_desc.load = true;
    shader_desc.vertex_src = "shaders/vertex.glsl";
    shader_desc.pixel_src = "shaders/pixel.glsl";
    shader_desc.source_type = PRIME_SHADER_SOURCE_TYPE_GLSL;
    primeShader* shader = primeCreateShader(context, shader_desc);

    while (!primeWindowShouldClose(window)) {
        primePullEvents();

        primeClear(context);
        primeSetShader(shader);
        primeSubmit(context, PRIME_DRAW_TYPE_ELEMENTS, PRIME_DRAW_MODE_TRIANGLES, 6);
        primePresent(context);
    }

    primeDestroyContext(context);
    primeDestroyWindow(window);
    return PRIME_PASSED;
}