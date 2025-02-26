
#include "prime/prime.h"

prime::Ref<prime::Context> g_Context;

void
onWindowResizeBuffers(const prime::Window* window, u32 width, u32 height)
{
    g_Context->setViewport({ 0.0f, 0.0f, (f32)width, (f32)height });
}

//#define USE_MULTIPLE_VBO

b8
buffersTestGL()
{
    using namespace prime;

    Window window;
    window.init("BuffersTestGL", 640, 480);

    Device device;
    device.init(DeviceType::OpenGL);

    g_Context = device.createContext(window);

#ifdef USE_MULTIPLE_VBO
    f32 vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
	};

    u32 indices[] = { 0, 1, 2, 2, 3, 0 };

    Ref<VertexArray> vertex_array;
    Ref<VertexBuffer> vertex_buffer;
    Ref<IndexBuffer> index_buffer;

    Layout layout;
    layout.addElement(Type::Float3);
    layout.addElement(Type::Float4);
    layout.addElement(Type::Float2);
    layout.process();

    vertex_array = device.createVertexArray();
    vertex_buffer = device.createStaticVertexBuffer(vertices, sizeof(vertices));
    vertex_buffer->setLayout(layout);
    index_buffer = device.createIndexBuffer(indices, 6);

    vertex_array->submit(vertex_buffer);

#else
    f32 pos_vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

    f32 color_vertices[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

    f32 tex_vertices[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f
	};

    u32 indices[] = { 0, 1, 2, 2, 3, 0 };

    Ref<VertexArray> vertex_array;
    Ref<VertexBuffer> pos_vertex_buffer;
    Ref<VertexBuffer> color_vertex_buffer;
    Ref<VertexBuffer> tex_vertex_buffer;
    Ref<IndexBuffer> index_buffer;

    Layout pos_layout;
    pos_layout.addElement(Type::Float3);
    pos_layout.process();

    Layout color_layout;
    color_layout.addElement(Type::Float4);
    color_layout.process();

    Layout tex_layout;
    tex_layout.addElement(Type::Float2);
    tex_layout.process();

    vertex_array = device.createVertexArray();

    pos_vertex_buffer = device.createStaticVertexBuffer(pos_vertices, sizeof(pos_vertices));
    pos_vertex_buffer->setLayout(pos_layout);

    color_vertex_buffer = device.createStaticVertexBuffer(color_vertices, sizeof(color_vertices));
    color_vertex_buffer->setLayout(color_layout);

    tex_vertex_buffer = device.createStaticVertexBuffer(tex_vertices, sizeof(tex_vertices));
    tex_vertex_buffer->setLayout(tex_layout);

    index_buffer = device.createIndexBuffer(indices, 6);

    g_Context->setVertexBuffer(pos_vertex_buffer);
    vertex_array->submit(pos_vertex_buffer);

    g_Context->setVertexBuffer(color_vertex_buffer);
    vertex_array->submit(color_vertex_buffer);

    g_Context->setVertexBuffer(tex_vertex_buffer);
    vertex_array->submit(tex_vertex_buffer);

#endif

    ShaderDesc shader_desc;
    shader_desc.load = true;
    shader_desc.vertex = "shaders/vertex.glsl";
    shader_desc.pixel = "shaders/pixel.glsl";
    shader_desc.type = ShaderSourceType::GLSL;

    Ref<Shader> shader;
    Ref<Texture> texture;

    shader = device.createShader(shader_desc);
    texture = device.createTexture("textures/texture2d.png");

    Ref<Texture> target;
    target = device.createTexture(1280, 720, TextureUsage::RenderTarget);

    Window::setResizeCallback(onWindowResizeBuffers);

    while (!window.shouldClose()) {
        window.pollEvents();

        g_Context->setTexture(texture);
        g_Context->setRenderTarget(target);
        g_Context->setClearColor({ 1.0f, 0.0f, 0.0f, 1.0f });
        g_Context->clear();

        g_Context->drawElements(DrawMode::Triangles, index_buffer->getCount());
        g_Context->setRenderTarget(nullptr);

        // draw render target
        g_Context->setClearColor({ .2f, .2f, .2f, 1.0f });
        g_Context->clear();
        g_Context->setTexture(target);

        g_Context->drawElements(DrawMode::Triangles, index_buffer->getCount());

        g_Context->present();
    }

    return PTRUE;
}