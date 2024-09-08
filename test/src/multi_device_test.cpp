
#include "prime/prime.h"

static b8 s_Running = false;

static void OnWndowClose(const prime::Window*)
{
	s_Running = false;
}

b8 MultiDeviceTest()
{
	prime::Window windowDirectX11;
	prime::WindowProperties directx11Props;
	directx11Props.Title = "DirectX11Window";
	windowDirectX11.Init(directx11Props);
	prime::Device directX11Device;
	directX11Device.Init(prime::DeviceTypeDirectX11, &windowDirectX11);
	directX11Device.SetClearColor(.2f, .2f, .2f, 1.0f);

	prime::Window windowOpenGL;
	prime::WindowProperties openGLProps;
	openGLProps.Title = "OpenGLWindow";
	windowOpenGL.Init(openGLProps);
	prime::Device openGLDevice;
	openGLDevice.Init(prime::DeviceTypeOpenGL, &windowOpenGL);
	openGLDevice.SetClearColor(.2f, .2f, .2f, 1.0f);

	prime::SetWindowCloseCallback(OnWndowClose);
	s_Running = true;

	while (s_Running)
	{
		prime::PollEvents();

		directX11Device.Clear();
		directX11Device.SwapBuffers();

		openGLDevice.Clear();
		openGLDevice.SwapBuffers();
	}

	directX11Device.Shutdown();
	openGLDevice.Shutdown();

	return PPASSED;
}