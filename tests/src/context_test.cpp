
#include "prime/prime.h"

b8 contextTest(void* data)
{
    primeWindowDesc desc;
    desc.size.x = 640;
    desc.size.y = 480;
    desc.title = "window";
    desc.flag = primeWindowFlags_Center;
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

    primeLayout* layout = primeCreateLayout();
    primeAddAttrib(layout, primeDataTypes_Float3, 0, false);

    primeBufferDesc buffer_desc;
    buffer_desc.data = vertices;
    buffer_desc.size = sizeof(vertices);
    buffer_desc.type = primeBufferTypes_Vertex;
    buffer_desc.usage = primeBufferUsages_Static;
    primeBuffer* vertex_buffer = primeCreateBuffer(buffer_desc);

    buffer_desc.data = indices;
    buffer_desc.size = sizeof(indices);
    buffer_desc.type = primeBufferTypes_Index;
    buffer_desc.usage = primeBufferUsages_Static;
    primeBuffer* index_buffer = primeCreateBuffer(buffer_desc);

    primeBindLayout(layout);

    primeShaderDesc shader_desc;
    shader_desc.load = true;
    shader_desc.vertex_src = "shaders/vertex.glsl";
    shader_desc.pixel_src = "shaders/pixel.glsl";
    shader_desc.source_type = primeShaderSourceTypes_GLSL;
    primeShader* shader = primeCreateShader(shader_desc);

    primeTextureDesc texture_desc;
    texture_desc.flag = primeTextureFlags_Target;
    texture_desc.format = primeTextureFormat_RGBA8;
    texture_desc.size = { 100, 100 };
    
    while (!primeWindowShouldClose(window)) {
        primePullEvents();

        primeClear(context);
        primeBindShader(shader);
        primeSubmit(context, primeDrawTypes_Element, primeDrawModes_Triangles, 6);
        primePresent(context);
    }

    primeDestroyContext(context);
    primeDestroyWindow(window);
    return PRIME_PASSED;
}