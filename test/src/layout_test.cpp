
#include "prime/prime.h"

b8
layoutTestGL()
{
    primeDevice* device = primeDeviceCreate(primeDeviceTypeGL);
    primeWindow* window = primeWindowCreate("Layout Test", 640, 480);
    primeContext* context = primeContextCreate(device, window);

    primeColor color = primeColorFromF32(.2f, .2f, .2f, 1.0f);
    primeContextSetClearColor(context, &color);

    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	u32 indices[] = { 0, 1, 2 };

    primeVertexbufferDesc vbo_desc;
    vbo_desc.size = sizeof(vertices);
    vbo_desc.data = vertices;
    vbo_desc.type = primeBufferTypeStatic;

    primeIndexbufferDesc ibo_desc;
    ibo_desc.count = 3;
    ibo_desc.indices = indices;

    primeShaderDesc shader;
    shader.load = true;
    shader.type = primeShaderTypeGLSL;
    shader.vertex = "shaders/vertex.glsl";
    shader.pixel = "shaders/pixel.glsl";

    primeLayoutDesc layout_desc;
    layout_desc.ibo = ibo_desc;
    layout_desc.vbo = vbo_desc;
    layout_desc.shader = shader;

    primeConstantbuffer* uniform_block = nullptr;
    uniform_block = primeConstantbufferCreate(device, sizeof(primeMat4), 0);

    primeConstantbufferBind(uniform_block);
    primeMat4 matrix = primeMat4Identity();
    primeConstantbufferSetData(uniform_block, &matrix, sizeof(primeMat4));

    primeLayout* layout = primeLayoutCreate(device, &layout_desc);
    primeLayoutBind(layout);
    primeLayoutAdd(layout, primeTypeFloat3);
    primeLayoutSubmit(layout);

    while (!primeWindowShouldClose(window)) {
        primeWindowPollEvents();

        primeContextClear(context);

        primeContextDrawElements(context, primeDrawModeTriangles, primeLayoutGetCount(layout));
        primeContextSwapbuffers(context);
    }

    primeDeviceDestroy(device);
    primeWindowDestroy(window);

    return true;
}