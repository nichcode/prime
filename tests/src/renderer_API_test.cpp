
#include "prime/prime.h"

b8 rendererAPITestGL()
{
    using namespace prime::core;
    using namespace prime::renderer;

    Scope<Window> window = Platform::createWindow("RendererAPITestGL", 640, 480);
    Scope<RendererAPI> rendererAPI = Platform::createAPI(prime::GraphicsAPIGL, window);
    rendererAPI->setClearColor({ .2f, .2f, .2f, 1.0f });

    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
	};

    u32 indices[] = { 0, 1, 2, 2, 3, 0 };

    VertexArray* vertex_array = rendererAPI->createVertexArray();
    VertexBuffer* vertex_buffer = rendererAPI->createStaticVertexBuffer(vertices, sizeof(vertices));
    IndexBuffer* index_buffer = rendererAPI->createIndexBuffer(indices, 6);
    Layout* layout = rendererAPI->createLayout();
    rendererAPI->AddElement(layout, prime::DataTypeFloat3);
    rendererAPI->AddElement(layout, prime::DataTypeFloat4);
    rendererAPI->AddElement(layout, prime::DataTypeFloat2);

    rendererAPI->setLayout(layout);

    Shader* shader = rendererAPI->createShader("shaders/vertex.glsl", "shaders/pixel.glsl");
    Texture* texture = rendererAPI->loadTexture("textures/texture2d.png");

    rendererAPI->setShader(shader);
    rendererAPI->upload(shader, "u_Texture", 0);
    rendererAPI->setTexture(texture);

    while (!window->shouldClose()) {
        Window::pollEvents();

        rendererAPI->clear();

        u32 count = rendererAPI->getIndexBufferCount(index_buffer);
        rendererAPI->submit(prime::DrawTypeElements, prime::DrawModeTriangles, count);

        rendererAPI->present();
    }

    return PRIME_TRUE;
}
