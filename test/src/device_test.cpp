
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
	prime::Window windowOpenGL;
	prime::WindowProperties propsOpenGL;
	propsOpenGL.Title = "WindowOpenGL";
	windowOpenGL.Init(propsOpenGL);

	prime::Device openGLDevice;
	openGLDevice.Init(prime::DeviceTypeOpenGL, &windowOpenGL);
	openGLDevice.SetClearColor(.2f, .2f, .2f, 1.0f);

	prime::SetWindowCloseCallback(OnWndowCloseOpenGL);
	s_RunningOpenGL = true;

	// resoures
	prime::Ref<prime::Vertexbuffer> openGLVertexbuffer;
	openGLVertexbuffer = openGLDevice.CreateVertexBuffer(16, prime::VertexbufferTypeStatic);

	while (s_RunningOpenGL)
	{
		prime::PollEvents();

		openGLDevice.Clear();
		openGLDevice.SwapBuffers();
	}

	openGLDevice.Shutdown();
	windowOpenGL.Destroy();

	return PPASSED;
}