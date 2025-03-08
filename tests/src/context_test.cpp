
#include "prime/prime.h"

b8 contextTestGL()
{
    using namespace prime;
    using namespace prime::core;
    using namespace prime::renderer;

    Window window;
    window.init("ContextTestGL", 640, 480);

    Scope<Context> context = Context::create(GraphicsAPIGL, window);
    context->setVsync(true);
    context->setClearColor({ .2f, .2f, .2f, 1.0f });

    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f, 
		 0.5f, -0.5f, 0.0f, 
		 0.0f,  0.5f, 0.0f  
	};

    u32 indices[] = { 0, 1, 2 };

    VertexArray vao = context->createVertexArray();
    VertexBuffer vbo = context->createVertexBuffer(vertices, sizeof(vertices));
    IndexBuffer ibo = context->createIndexBuffer(indices, 3);

    while (!window.shouldClose()) {
        window.pollEvents();

        context->clear();

        context->present();
    }

    return PRIME_TRUE;
}