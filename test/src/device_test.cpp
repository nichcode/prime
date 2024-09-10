
#include "prime/prime.h"

b8 s_RunningOpenGL = false;
b8 s_RunningDirectx11 = false;

void OnWndowCloseDirectx11(const prime::Window*)
{
	s_RunningDirectx11 = false;
}

void OnWndowCloseOpenGL(const prime::Window*)
{
	s_RunningOpenGL = false;
}

b8 DirectX11DeviceTest()
{
	prime::Window windowDirectx11;
	prime::WindowProperties propsDirectx11;
	propsDirectx11.Title = "WindowDirectx11";
	windowDirectx11.Init(propsDirectx11);

	prime::Device directX11Device;
	directX11Device.Init(prime::DeviceTypeDirectX11, &windowDirectx11);
	directX11Device.SetClearColor(.2f, .2f, .2f, 1.0f);

	prime::SetWindowCloseCallback(OnWndowCloseDirectx11);
	s_RunningDirectx11 = true;

	u32 indices[3] = { 0,1, 2 };

	// resources
	prime::Ref<prime::Vertexbuffer> vertexbuffer;
	prime::Ref<prime::Indexbuffer> indexbuffer;
	vertexbuffer = directX11Device.CreateVertexBuffer(nullptr, 200, prime::VertexbufferTypeStatic);
	indexbuffer = directX11Device.CreateIndexBuffer(indices, 3);

	while (s_RunningDirectx11)
	{
		prime::PollEvents();

		directX11Device.Clear();
		directX11Device.SwapBuffers();
	}

	windowDirectx11.Destroy();
	directX11Device.Shutdown();

	return PPASSED;
}

b8 OpenGLDeviceTest()
{
	prime::Window window;
	prime::WindowProperties props;
	props.Title = "WindowOpenGL";
	window.Init(props);

	prime::Device device;
	device.Init(prime::DeviceTypeOpenGL, &window);
	device.SetClearColor(.2f, .2f, .2f, 1.0f);

	prime::SetWindowCloseCallback(OnWndowCloseOpenGL);
	s_RunningOpenGL = true;

	// resoures
	prime::Ref<prime::Vertexbuffer> vertexbuffer;
	prime::Ref<prime::Indexbuffer> indexbuffer;

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

	while (s_RunningOpenGL)
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