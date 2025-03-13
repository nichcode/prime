
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

    Ref<VertexArray> vertex_array = rendererAPI->createVertexArray();
    Ref<VertexBuffer> vertex_buffer = rendererAPI->createStaticVertexBuffer(vertices, sizeof(vertices));
    Ref<IndexBuffer> index_buffer = rendererAPI->createIndexBuffer(indices, 6);
    Layout layout;
    layout.add(prime::DataTypeFloat3);
    layout.add(prime::DataTypeFloat4);
    layout.add(prime::DataTypeFloat2);
    layout.process();

    vertex_array->setLayout(layout);
    Ref<Shader> shader = rendererAPI->createShader("shaders/vertex.glsl", "shaders/pixel.glsl");
    shader->bind();
    shader->setInt("u_Texture", 0);

    Ref<Texture> texture = rendererAPI->loadTexture("textures/texture2d.png");
    texture->bind();

    while (!window->shouldClose()) {
        Window::pollEvents();

        rendererAPI->clear();
        rendererAPI->submit(prime::DrawTypeElements, prime::DrawModeTriangles, index_buffer->getCount());
        rendererAPI->present();
    }

    return PRIME_TRUE;
}
