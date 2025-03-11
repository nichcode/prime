
#include "prime/prime.h"

b8 rendererAPITestGL()
{
    using namespace prime::core;
    using namespace prime::renderer;

    Scope<Window> window = Platform::createWindow("WindowTest", 640, 480);
    Scope<RendererAPI> rendererAPI = Platform::createAPI(prime::GraphicsAPIGL, window);
    rendererAPI->setClearColor({ .2f, .2f, .2f, 1.0f });

    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
	};

    u32 indices[] = { 0, 1, 2, 2, 3, 0 };

    VertexArray* vertex_array = rendererAPI->createVertexArray();
    VertexBuffer* vertex_buffer = rendererAPI->createStaticVertexBuffer(vertices, sizeof(vertices));
    IndexBuffer* index_buffer = rendererAPI->createIndexBuffer(indices, 6);
    Layout* layout = rendererAPI->createLayout();
    rendererAPI->AddElement(layout, prime::DataTypeFloat3);

    rendererAPI->setLayout(layout);

    Shader* shader = rendererAPI->createShader("shaders/vertex.glsl", "shaders/pixel.glsl");

    while (!window->shouldClose()) {
        Window::pollEvents();

        rendererAPI->clear();

        rendererAPI->setShader(shader);
        u32 count = rendererAPI->getIndexBufferCount(index_buffer);
        rendererAPI->submit(prime::DrawTypeElements, prime::DrawModeTriangles, count);

        rendererAPI->present();
    }

    return PRIME_TRUE;
}
