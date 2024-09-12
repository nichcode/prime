
#include "prime/prime.h"

b8 s_Running = false;
prime::Window window;
prime::Device device;

void OnWndowClose(const prime::Window*)
{
	s_Running = false;
}

void OnWndowResize(const prime::Window*, u32 width, u32 height)
{
	prime::Viewport view;
	view.Width = width;
	view.Height = height;
	device.SetViewport(view);
}

b8 DeviceTest()
{
	prime::WindowProperties props;
	prime::DeviceType type = prime::DeviceTypeOpenGL;

	if (type == prime::DeviceTypeDirectX11) {
		props.Title = "WindowOpenGL";
	}
	else if (type == prime::DeviceTypeOpenGL) {
		props.Title = "WindowOpenGL";
	}
	window.Init(props);

	device.Init(type, &window);
	device.SetClearColor(.2f, .2f, .2f, 1.0f);

	prime::SetWindowCloseCallback(OnWndowClose);
	prime::SetWindowResizeCallback(OnWndowResize);
	s_Running = true;

	// resoures
	prime::Ref<prime::Vertexbuffer> vertexbuffer;
	prime::Ref<prime::Indexbuffer> indexbuffer;
	prime::Ref<prime::Shader > shader;
	prime::Viewport viewport;
	viewport.Width = window.GetWidth();
	viewport.Height = window.GetHeight();

	device.SetViewport(viewport);

	f32 vertices[6] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.0f,  0.5f,
	};

	prime::VertexbufferLayout layout;
	layout.AddBufferElement({ prime::DataTypeFloat2 });
	layout.ProcessElements();
	vertexbuffer = device.CreateVertexBuffer(vertices, sizeof(vertices), prime::VertexbufferTypeStatic);
	vertexbuffer->SetLayout(layout);

	u32 indices[3] = { 0,1, 2 };
	indexbuffer = device.CreateIndexBuffer(indices, sizeof(indices) / sizeof(u32));
	indexbuffer->Bind();

	shader = device.CreateShader("shaders/flat_color_vertex.glsl", "shaders/flat_color_pixel.glsl", true);
	shader->Bind();

	while (s_Running)
	{
		prime::PollEvents();

		device.Clear();
		device.DrawIndexed(prime::PrimitiveTopologyTriangles, indexbuffer->GetCount());
		device.SwapBuffers();
	}

	device.Shutdown();
	window.Destroy();

	return PPASSED;
}