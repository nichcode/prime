
#include "prime/prime.h"

//#define USE_MULTIPLE_VBO

b8
buffersTestGL()
{
    prime::Window window;
    window.init("WindowTest", 640, 480);

    prime::Device device;
    device.init(prime::DeviceType::OpenGL);

    prime::Context* context = device.createContext(window);
    context->setClearColor({ .2f, .2f, .2f, 1.0f });

#ifdef USE_MULTIPLE_VBO
    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // left  
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // right 
		 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f // top   
	};

    u32 indices[] = { 0, 1, 2 };

    prime::VertexArray* vertex_array;
    prime::VertexBuffer* vertex_buffer;
    prime::IndexBuffer* index_buffer;
    prime::Shader* shader = nullptr;

    prime::Layout layout;
    layout.addElement(prime::Type::Float3);
    layout.addElement(prime::Type::Float4);
    layout.process();

    vertex_array = context->createVertexArray();
    vertex_buffer = context->createStaticVertexBuffer(vertices, sizeof(vertices));
    vertex_buffer->setLayout(layout);
    index_buffer = context->createIndexBuffer(indices, 3);

    vertex_array->submit(vertex_buffer);

#else
    f32 pos_vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

    f32 color_vertices[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f
	};

    u32 indices[] = { 0, 1, 2 };

    prime::VertexArray* vertex_array;
    prime::VertexBuffer* pos_vertex_buffer;
    prime::VertexBuffer* color_vertex_buffer;
    prime::IndexBuffer* index_buffer;
    prime::Shader* shader = nullptr;

    prime::Layout pos_layout;
    pos_layout.addElement(prime::Type::Float3);
    pos_layout.process();

    prime::Layout color_layout;
    color_layout.addElement(prime::Type::Float4);
    color_layout.process();

    vertex_array = context->createVertexArray();

    pos_vertex_buffer = context->createStaticVertexBuffer(pos_vertices, sizeof(pos_vertices));
    pos_vertex_buffer->setLayout(pos_layout);

    color_vertex_buffer = context->createStaticVertexBuffer(color_vertices, sizeof(color_vertices));
    color_vertex_buffer->setLayout(color_layout);

    index_buffer = context->createIndexBuffer(indices, 3);

    context->setVertexBuffer(pos_vertex_buffer);
    vertex_array->submit(pos_vertex_buffer);

    context->setVertexBuffer(color_vertex_buffer);
    vertex_array->submit(color_vertex_buffer);

#endif

    prime::ShaderDesc shader_desc;
    shader_desc.load = true;
    shader_desc.vertex = "shaders/vertex.glsl";
    shader_desc.pixel = "shaders/pixel.glsl";
    shader_desc.type = prime::ShaderSourceType::GLSL;

    shader = context->createShader(shader_desc);;

    while (!window.shouldClose()) {
        window.pollEvents();

        context->clear();
        context->drawElements(prime::DrawMode::Triangles, index_buffer->getCount());
        context->swapbuffers();
    }

    return PTRUE;
}