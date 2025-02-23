
#include "prime/prime.h"

b8
buffersTestGL()
{
    prime::Window window;
    window.init("WindowTest", 640, 480);

    prime::Device device;
    device.init(prime::DeviceType::OpenGL);

    prime::Context* context = device.createContext(window);
    context->setClearColor({ .2f, .2f, .2f, 1.0f });

    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	u32 indices[] = { 0, 1, 2 };

    prime::BufferDesc vbo_desc;
    vbo_desc.data = vertices;
    vbo_desc.size = sizeof(vertices);
    vbo_desc.type = prime::BufferType::Vertex;
    vbo_desc.usage = prime::BufferUsage::StaticDraw;

    prime::BufferDesc ibo_desc;
    ibo_desc.data = indices;
    ibo_desc.size = sizeof(indices);
    ibo_desc.type = prime::BufferType::Index;
    ibo_desc.usage = prime::BufferUsage::StaticDraw;

    prime::Layout* layout = context->createLayout();
    layout->add(prime::Type::Float3);
    prime::Buffer* vbo = context->createBuffer(vbo_desc);
    prime::Buffer* ibo = context->createBuffer(ibo_desc);

    context->setLayout(layout, true);
    context->setBuffer(vbo);
    context->setBuffer(ibo);

    layout->submit();

    while (!window.shouldClose()) {
        window.pollEvents();

        context->clear();
        context->drawElements(prime::DrawMode::Triangles, 3);
        context->swapbuffers();
    }

    return PTRUE;
}