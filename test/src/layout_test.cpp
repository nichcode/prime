
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

    primeLayout* layout = primeLayoutCreate(device, vbo_desc, ibo_desc);
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